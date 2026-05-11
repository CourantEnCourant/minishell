/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:34:51 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/30 21:13:23 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"

int			exec_pipe(t_btree *ast, t_env *env);
bool		apply_redirs(t_cmd *cmd, t_env *env);
void		execute(t_btree *ast, t_env *env);
void		exec_builtins(char *cmd, char **options, t_env *env);
bool		strs_eq(void *s1, void *s2);

static void	exec_builtin_cmd(t_cmd *cmd, t_env *env)
{
	int		saved_stdin;
	int		saved_stdout;
	char	**argv;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirs(cmd, env))
	{
		expand_cmd(cmd, env);
		argv = (char **)cmd->argv->to_arr(cmd->argv);
		exec_builtins(argv[0], argv, env);
	}
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static void	exec_fork_child(t_cmd *cmd, t_env *env)
{
	int		status;
	char	**argv;

	if (apply_redirs(cmd, env))
	{
		expand_cmd(cmd, env);
		argv = (char **)cmd->argv->to_arr(cmd->argv);
		status = gc_execvp(argv[0], argv,
				(char **)env->envp->to_arr(env->envp), env->gc);
	}
	else
		status = env->exit_code;
	env->gc->clean(env->gc);
	exit(status);
}

static void	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	if (env->builtins->any(env->builtins, strs_eq, cmd->argv->peek_i(cmd->argv, 0)))
	{
		exec_builtin_cmd(cmd, env);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		env->exit_code = 1;
		return ;
	}
	if (pid == 0)
		exec_fork_child(cmd, env);
	waitpid(pid, &status, 0);
	env->exit_code = status >> 8;
}

void	exec_subshell(t_btree *ast, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		env->exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		execute(ast->left, env);
		status = env->exit_code;
		ast->gc->clean(ast->gc);
		exit(status);
	}
	waitpid(pid, &status, 0);
	env->exit_code = status >> 8;
}

void	execute(t_btree *ast, t_env *env)
{
	t_token	*current;

	current = ast->value;
	if (current->type == CMD)
		exec_cmd(current->cmd, env);
	else if (current->type == AND)
	{
		execute(ast->left, env);
		if (env->exit_code == 0)
			execute(ast->right, env);
	}
	else if (current->type == OR)
	{
		execute(ast->left, env);
		if (env->exit_code != 0)
			execute(ast->right, env);
	}
	else if (current->type == PIPE)
		exec_pipe(ast, env);
	else if (current->type == SUBSHELL)
		exec_subshell(ast, env);
}
