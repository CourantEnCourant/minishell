/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:37:33 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/11 13:38:19 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

int	main(void)
{
	char		*input;
	t_gc		*gc;
	t_darray	*tokens;
	t_btree		*ast;
	t_parser	*parser;

	gc = init_gc();
	parser = init_parser(gc);
	while (true)
	{
		input = gc_readline("minishell> ", gc);
		if (!input)
			break ;
		if (!parser->is_valid_cmd(input))
			continue ;
		tokens = parser->tokenize(input, gc);
		ast = parser->parse(tokens);
		if (!parser->is_valid_tree(ast))
			continue ;
		execute(ast);
	}
	printf("exit\n");
	gc->clean(gc);
}
