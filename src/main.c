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
#include "gc_libft.h"
#include "minishell.h"

int	main(void)
{
	char	*input;
	t_gc	*gc;

	gc = init_gc();
	while (true)
	{
		input = gc_readline("minishell> ", gc);
		if (!input)
			break ;
		printf("%s\n", input);
	}
	printf("exit\n");
	gc->clean(gc);
}
