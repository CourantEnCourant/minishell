/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 11:01:31 by fdong             #+#    #+#             */
/*   Updated: 2026/05/27 20:01:30 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include "minishell.h"

char	*expand_arg(char *arg, t_env *env);
void	*strip_sentinel(void *s, t_gc *gc);

char	*get_hd_filename(t_env *env)
{
	static int		counter;
	char			*p_str;
	unsigned long	mix_hash;

	mix_hash = (unsigned long)env + counter;
	counter++;
	p_str = gc_itoa((int)(mix_hash & 0xFF), env->gc);
	return (gc_strjoin("/tmp/.hd_", p_str, env->gc));
}

static void	hd_read_loop(char *delim, int fd, bool quoted, t_env *env)
{
	char	*line;

	while (true)
	{
		line = gc_readline("> ", env->gc);
		if (!line)
		{
			ft_dprintf(STDERR_FILENO,
				"here_document delimited by end-of-file (wanted '%s')\n",
				delim);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
			break ;
		if (!quoted)
			line = strip_sentinel(expand_arg(line, env), env->gc);
		ft_putendl_fd(line, fd);
	}
}

static void	hd_child_process(char *delim, char *file, bool q, t_env *env)
{
	int		fd;

	setup_signals_fork();
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("heredoc open");
		rl_clear_history();
		env->gc->clean(env->gc);
		exit(1);
	}
	hd_read_loop(delim, fd, q, env);
	close(fd);
	rl_clear_history();
	env->gc->clean(env->gc);
	exit(0);
}

bool	save_hd_input(char *delim, char *file, bool quoted, t_env *env)
{
	pid_t	pid;
	int		status;

	setup_signals_execution();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), false);
	if (pid == 0)
		hd_child_process(delim, file, quoted, env);
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		env->exit_code = 130;
		unlink(file);
		return (false);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		env->exit_code = WEXITSTATUS(status);
	return (true);
}

void	clear_ast_heredocs(t_btree *ast)
{
	t_token	*token;
	t_redir	*redir;
	size_t	i;

	if (!ast)
		return ;
	clear_ast_heredocs(ast->left);
	clear_ast_heredocs(ast->right);
	token = ast->value;
	if (token->type == CMD)
	{
		i = 0;
		while (i < token->cmd->redirs->len)
		{
			redir = token->cmd->redirs->peek_i(token->cmd->redirs, i);
			if (redir->redir_type == HERE_DOC && redir->filename)
			{
				if (ft_strncmp(redir->filename, "/tmp/.hd_", 9) == 0)
					unlink(redir->filename);
			}
			i++;
		}
	}
	return ;
}
