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

void		exec_child(t_btree *node, int in_fd, int out_fd, t_gc *gc);
t_darray	*flatten(t_btree *ast);

static int	setup_fds(int *fds, bool is_last)
{
	if (!is_last)
	{
		if (pipe(fds) == -1)
		{
			perror("pipe");
			return (-1);
		}
		return (0);
	}
	fds[0] = STDIN_FILENO;
	fds[1] = STDOUT_FILENO;
	return (0);
}

static void	fork_cleanup(int *fds, int *prev_fd)
{
	if (fds[1] != STDOUT_FILENO)
		close(fds[1]);
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	*prev_fd = fds[0];
}

static pid_t	fork_cmd(t_btree *node, int *prev_fd, bool is_last, t_gc *gc)
{
	pid_t	pid;
	int		fds[2];

	if (setup_fds(fds, is_last) == -1)
		return (-1);
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
	if (pid == 0 && fds[0] != STDIN_FILENO)
		close(fds[0]);
	if (pid == 0)
		exec_child(node, *prev_fd, fds[1], gc);
	fork_cleanup(fds, prev_fd);
	return (pid);
}

static int	wait_children(pid_t *pids, size_t len)
{
	size_t	i;
	int		status;

	i = 0;
	while (i < len)
	{
		if (pids[i] > 0)
			waitpid(pids[i], &status, 0);
		i++;
	}
	return (status >> 8);
}

int	exec_pipe(t_btree *ast)
{
	t_darray	*nodes;
	pid_t		*pids;
	int			prev_fd;
	size_t		i;

	nodes = flatten(ast);
	pids = gc_calloc(nodes->len, sizeof(pid_t), ast->gc);
	prev_fd = STDIN_FILENO;
	i = 0;
	while (i < nodes->len)
	{
		pids[i] = fork_cmd(nodes->peek_i(nodes, i),
				&prev_fd, i == nodes->len - 1, ast->gc);
		if (pids[i] == -1)
			break ;
		i++;
	}
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	if (i == 0)
		return (1);
	return (wait_children(pids, nodes->len));
}
