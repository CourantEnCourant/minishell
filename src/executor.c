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

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"

int			gc_execvp(const char *cmd, char *const argv[], t_gc *gc);
int			exec_pipe(t_btree *ast);
int			execute(t_btree *ast);

static int	exec_cmd(t_cmd *cmd, t_gc *gc)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exit_code = gc_execvp(cmd->argv[0], cmd->argv, gc);
		gc->clean(gc);
		exit(exit_code);
	}
	waitpid(pid, &status, 0);
	return (status >> 8);
}

int	exec_subshell(t_btree *ast)
{
	pid_t	pid;
	int		exit_code;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		exit_code = execute(ast->left);
		ast->gc->clean(ast->gc);
		exit(exit_code);
	}
	waitpid(pid, &status, 0);
	return (status >> 8);
}

static int	exec_and(t_btree *ast)
{
	int	status;

	status = execute(ast->left);
	if (status == 0)
		return (execute(ast->right));
	return (status);
}

int	execute(t_btree *ast)
{
	t_token	*current;
	int		status;

	current = ast->value;
	if (current->type == CMD)
		return (exec_cmd(current->cmd, ast->gc));
	else if (current->type == AND)
		return (exec_and(ast));
	else if (current->type == OR)
	{
		status = execute(ast->left);
		if (status != 0)
			return (execute(ast->right));
		return (status);
	}
	else if (current->type == PIPE)
		return (exec_pipe(ast));
	else if (current->type == SUBSHELL)
		return (exec_subshell(ast));
	else
		return (execute(ast->left));
}

