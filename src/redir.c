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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

static void	apply_to_file(t_redir *redir)
{
	int	fd;

	fd = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		redir->gc->clean(redir->gc);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirs(t_cmd *cmd)
{
	int		fd;
	t_redir	*redir;
	size_t	i;

	i = 0;
	while (i < cmd->redirs->len)
	{
		redir = cmd->redirs->peek_i(cmd->redirs, i);
		if (redir->redir_type == TO_FILE)
			apply_to_file(redir);
		else if (redir->redir_type == APPEND_FILE)
		{
			fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redir->redir_type == FROM_FILE)
		{
			fd = open(redir->filename, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		i++;
	}
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
