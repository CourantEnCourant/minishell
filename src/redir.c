/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:00:01 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/02 21:03:29 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

static int	apply_from_file(t_redir *redir)
{
	int	fd;
	int	flag;

	flag = 0;
	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		flag = 1;
	}
	close(fd);
	return (flag);
}

static int	apply_append_file(t_redir *redir)
{
	int	fd;
	int	flag;

	flag = 0;
	fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		flag = 1;
	}
	close(fd);
	return (flag);
}

static int	apply_to_file(t_redir *redir)
{
	int	fd;
	int	flag;

	flag = 0;
	fd = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		flag = 1;
	}
	close(fd);
	return (flag);
}

int	apply_redirs(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (i < cmd->redirs->len)
	{
		redir = cmd->redirs->peek_i(cmd->redirs, i);
		if (redir->redir_type == TO_FILE)
			flag = apply_to_file(redir);
		else if (redir->redir_type == APPEND_FILE)
			flag = apply_append_file(redir);
		else if (redir->redir_type == FROM_FILE)
			flag = apply_from_file(redir);
		if (flag != 0)
			break ;
		i++;
	}
	env->exit_code = flag;
	return (flag);
}

t_redir	*init_redir(t_redir_type redir_type, char *filename, t_gc *gc)
{
	t_redir	*redir;

	redir = gc_malloc(sizeof(t_redir), gc);
	redir->redir_type = redir_type;
	redir->filename = filename;
	redir->gc = gc;
	return (redir);
}
