/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:37:33 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/27 21:58:13 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"
#include <signal.h>

bool	loop(t_env *env)
{
	char		*input;
	t_btree		*ast;

	setup_signals_interactive();
	input = gc_readline("minishell> ", env->gc);
	if (g_signal == SIGINT)
	{
		env->exit_code = 130;
		g_signal = 0;
	}
	if (!input)
		return (false);
	if (!input[0])
		return (true);
	add_history(input);
	ast = parse(input, env);
	if (!ast)
		return (true);
	if (collect_heredocs(ast, env) == false)
		return (clear_ast_heredocs(ast), true);
	setup_signals_execution();
	execute(ast, env);
	clear_ast_heredocs(ast);
	return (true);
}

int	main(void)
{
	t_gc		*gc;
	t_env		*env;
	bool		flag;

	gc = init_gc();
	env = init_env(gc);
	flag = true;
	while (flag)
		flag = loop(env);
	printf("exit\n");
	rl_clear_history();
	gc->clean(gc);
}
