/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 20:07:52 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/16 21:42:28 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"
#include "datastructures.h"

void	exec_child(t_btree *node, int in_fd, int out_fd, t_gc *gc);

static pid_t	fork_cmd(t_btree *node, int *prev_fd, bool is_last, t_gc *gc)
{
	pid_t	pid;
	int		fds[2];

	if (!is_last)
	{
		if (pipe(fds) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	else
	{
		fds[0] = STDIN_FILENO;
		fds[1] = STDOUT_FILENO;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (fds[1] != STDOUT_FILENO)
		{
			close(fds[0]);
			close(fds[1]);
		}
		return (-1);
	}
	if (pid == 0)
	{
		if (fds[0] != STDIN_FILENO)
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
		if (pids[i] == -1)
			break ;
		i++;
	}
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	if (i == 0)
		return (1);
	i = 0;
	while (i < nodes->len)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &status, 0);
		i++;
	}
	return (status >> 8);
}
