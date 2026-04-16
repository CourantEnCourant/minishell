/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:43:24 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/02 21:07:16 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

static void	push_redir(t_cmd *self, t_redir *redir)
{
	self->redirs->push(self->redirs, redir);
}

static void	set_argv(t_cmd *self, char **argv)
{
	self->argv = argv;
}

t_cmd	*init_cmd(t_gc *gc)
{
	t_cmd	*cmd;

	cmd = gc_malloc(sizeof(t_cmd), gc);
	cmd->redirs = init_darray(gc);
	cmd->set_argv = set_argv;
	cmd->push_redir = push_redir;
	return (cmd);
}
