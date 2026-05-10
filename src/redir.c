/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:00:01 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/11 00:21:37 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

static bool	apply_from_file(t_redir *redir, t_env *env)
{
	int		fd;
	bool	flag;

	flag = true;
	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->filename);
		env->exit_code = 1;
		return (false);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		env->exit_code = 1;
		flag = false;
	}
	close(fd);
	return (flag);
}

static bool	apply_append_file(t_redir *redir, t_env *env)
{
	int		fd;
	bool	flag;

	flag = true;
	fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		env->exit_code = 1;
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		env->exit_code = 1;
		flag = false;
	}
	close(fd);
	return (flag);
}

static bool	apply_to_file(t_redir *redir, t_env *env)
{
	int		fd;
	bool	flag;

	flag = true;
	fd = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		env->exit_code = 1;
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		env->exit_code = 1;
		flag = false;
	}
	close(fd);
	return (flag);
}

bool	apply_redirs(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	bool	flag;
	size_t	i;

	flag = true;
	i = 0;
	while (i < cmd->redirs->len)
	{
		redir = cmd->redirs->peek_i(cmd->redirs, i);
		if (redir->redir_type == TO_FILE)
			flag = apply_to_file(redir, env);
		else if (redir->redir_type == APPEND_FILE)
			flag = apply_append_file(redir, env);
		else if (redir->redir_type == FROM_FILE)
			flag = apply_from_file(redir, env);
		if (!flag)
			break ;
		i++;
	}
	return (flag);
}

static void	set_filename(t_redir *self, char *filename)
{
	self->filename = filename;
}

t_redir	*init_redir(t_redir_type redir_type, char *filename, t_gc *gc)
{
	t_redir	*redir;

	redir = gc_malloc(sizeof(t_redir), gc);
	redir->redir_type = redir_type;
	redir->filename = filename;
	redir->set_filename = set_filename;
	redir->gc = gc;
	return (redir);
}
