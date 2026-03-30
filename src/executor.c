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

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"

int			gc_execvp(const char *cmd, char *const argv[], t_gc *gc);
static int	execute(t_btree *ast);

static int	exec_operand(t_token *operand, t_gc *gc)
{
	pid_t	pid;
	char	**cmds;
	int		exit_code;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		cmds = gc_split(operand->value, ' ', gc);
		exit_code = gc_execvp(cmds[0], cmds, gc);
		gc->clean(gc);
		exit(exit_code);
	}
	wait(&status);
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

static int	execute(t_btree *ast)
{
	t_token	*current;

	current = ast->value;
	if (current->type == OPERAND)
		return (exec_operand(current, ast->gc));
	else if (current->type == AND)
		return (exec_and(ast));
	else
		return (execute(ast->left));
}

t_exec	*init_exec(t_gc *gc)
{
	t_exec	*executor;

	executor = gc_malloc(sizeof(t_exec), gc);
	executor->execute = execute;
	executor->gc = gc;
	return (executor);
}
