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

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

int	main(void)
{
	char		*input;
	t_gc		*gc;
	t_btree		*ast;
	t_env		*env;

	gc = init_gc();
	env = init_env(gc);
	while (true)
	{
		input = gc_readline("minishell> ", gc);
		if (!input)
			break ;
		add_history(input);
		ast = parse(input, env, gc);
		if (!ast)
			continue ;
		execute(ast);
	}
	printf("exit\n");
	rl_clear_history();
	gc->clean(gc);
}
