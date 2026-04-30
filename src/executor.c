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

int			gc_execvp(const char *cmd, char *const argv[], t_gc *gc);
int			exec_pipe(t_btree *ast);
void		apply_redirs(t_cmd *cmd);
void		execute(t_btree *ast, t_env *env);

static void	exec_cmd(t_cmd *cmd, t_gc *gc, t_env *env)
{
	pid_t	pid;
	int		exit_code;
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
		apply_redirs(cmd);
		exit_code = gc_execvp(cmd->argv[0], cmd->argv, gc);
		gc->clean(gc);
		exit(exit_code);
	}
	waitpid(pid, &status, 0);
	env->exit_code = status >> 8;
}

int	exec_subshell(t_btree *ast, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execute(ast->left, env);
		ast->gc->clean(ast->gc);
		exit(env->exit_code);
	}
	waitpid(pid, &status, 0);
	return (status >> 8);
}

static void	exec_and(t_btree *ast, t_env *env)
{
	execute(ast->left, env);
	if (env->exit_code == 0)
		execute(ast->right, env);
}

void	execute(t_btree *ast, t_env *env)
{
	t_token	*current;

	current = ast->value;
	if (current->type == CMD)
		exec_cmd(current->cmd, ast->gc, env);
	else if (current->type == AND)
		exec_and(ast, env);
	else if (current->type == OR)
	{
		execute(ast->left, env);
		if (env->exit_code != 0)
			execute(ast->right, env);
	}
	else if (current->type == PIPE)
		exec_pipe(ast);
	else if (current->type == SUBSHELL)
		exec_subshell(ast, env);
	else
		execute(ast->left, env);
}
