/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:00:01 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/26 20:44:01 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
