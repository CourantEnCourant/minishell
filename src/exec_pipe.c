/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 20:07:52 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"
#include "datastructures.h"

int		gc_execvp(const char *cmd, char *const argv[], t_gc *gc);
int		exec_subshell(t_btree *ast);
void	apply_redirs(t_cmd *cmd);

static void	exec_child(t_btree *node, int in_fd, int out_fd, t_gc *gc)
{
	t_token	*token;
	t_cmd	*cmd;
	int		exit_code;

	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	token = node->value;
	if (token->type == CMD)
	{
		cmd = token->cmd;
		apply_redirs(cmd);
		exit_code = gc_execvp(cmd->argv[0], cmd->argv, gc);
		gc->clean(gc);
		exit(exit_code);
	}
	exit_code = exec_subshell(node);
	gc->clean(gc);
	exit(exit_code);
}

static pid_t	fork_cmd(t_btree *node, int *prev_fd, bool is_last, t_gc *gc)
{
	pid_t	pid;
	int		fds[2];

	if (!is_last)
		pipe(fds);
	else
	{
		fds[0] = -1;
		fds[1] = STDOUT_FILENO;
	}
	pid = fork();
	if (pid == 0)
	{
		if (fds[0] != -1)
			close(fds[0]);
		exec_child(node, *prev_fd, fds[1], gc);
	}
	if (fds[1] != STDOUT_FILENO)
		close(fds[1]);
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	*prev_fd = fds[0];
	return (pid);
}

static void	flatten_recur(t_btree *ast, t_darray *nodes)
{
	t_token		*current;

	current = ast->value;
	if (current->type == CMD || current->type == SUBSHELL)
		nodes->push(nodes, ast);
	if (current->type == PIPE)
	{
		flatten_recur(ast->left, nodes);
		flatten_recur(ast->right, nodes);
	}
}

t_darray	*flatten(t_btree *ast)
{
	t_darray	*nodes;

	nodes = init_darray(ast->gc);
	flatten_recur(ast, nodes);
	return (nodes);
}

int	exec_pipe(t_btree *ast)
{
	t_darray	*nodes;
	pid_t		*pids;
	int			prev_fd;
	int			status;
	size_t		i;

	nodes = flatten(ast);
	pids = gc_calloc(nodes->len, sizeof(pid_t), ast->gc);
	prev_fd = STDIN_FILENO;
	i = 0;
	while (i < nodes->len)
	{
		if (i < nodes->len - 1)
			pids[i] = fork_cmd(nodes->peek_i(nodes, i),
					&prev_fd, false, ast->gc);
		else
			pids[i] = fork_cmd(nodes->peek_i(nodes, i),
					&prev_fd, true, ast->gc);
		i++;
	}
	i = 0;
	while (i < nodes->len)
		waitpid(pids[i++], &status, 0);
	return (status >> 8);
}
