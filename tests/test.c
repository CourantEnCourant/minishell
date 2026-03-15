/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:54:54 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/11 13:55:27 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

void	test_parser(t_gc *gc)
{
	t_parser	*parser;
	t_darray	*cmds;

	parser = init_parser(gc);
	cmds = parser->tokenize("ls -l|grep -la", gc);
	cmds->repr(cmds);
}

int main(void)
{
	t_gc	*gc;

	gc = init_gc();
	test_parser(gc);
	gc->clean(gc);
}
