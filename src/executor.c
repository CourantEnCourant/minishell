/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:34:51 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/27 16:15:27 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"

int			exec_pipe(t_btree *ast, t_env *env);
int			apply_redirs(t_cmd *cmd);
int			execute(t_btree *ast, t_env *env);

static int	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		exit_code = apply_redirs(cmd);
		if (exit_code == 0)
			exit_code = gc_execvp(cmd->argv[0], cmd->argv, env->gc);
		env->gc->clean(env->gc);
		exit(exit_code);
	}
	waitpid(pid, &status, 0);
	return (status >> 8);
}

int	exec_subshell(t_btree *ast, t_env *env)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		exit_code = execute(ast->left, env);
		ast->gc->clean(ast->gc);
		exit(exit_code);
	}
	waitpid(pid, &status, 0);
	return (status >> 8);
}

static int	exec_and(t_btree *ast, t_env *env)
{
	int	status;

	status = execute(ast->left, env);
	if (status == 0)
		return (execute(ast->right, env));
	return (status);
}

int	execute(t_btree *ast, t_env *env)
{
	t_token	*current;
	int		status;

	current = ast->value;
	if (current->type == CMD)
		return (exec_cmd(current->cmd, env));
	else if (current->type == AND)
		return (exec_and(ast, env));
	else if (current->type == OR)
	{
		status = execute(ast->left, env);
		if (status != 0)
			return (execute(ast->right, env));
		return (status);
	}
	else if (current->type == PIPE)
		return (exec_pipe(ast, env));
	else if (current->type == SUBSHELL)
		return (exec_subshell(ast, env));
	else
		return (execute(ast->left, env));
}
