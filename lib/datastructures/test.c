/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:12:32 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/02 21:34:49 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include "gc_libft.h"
#include "datastructures.h"

void	test_darray(t_gc *gc)
{
	t_darray	*list;

	printf("==========darray test==========\n");
	list = init_darray(gc);
	printf("Test empty darray\n");
	list->repr(list);
	printf("\n");

	printf("Test pop() from empty darray\n");
	list->pop(list);
	list->repr(list);
	printf("\n");

	printf("Test pop_i() from empty darray\n");
	list->pop_i(list, 1);
	list->repr(list);
	printf("\n");


	printf("Test peep() from empty darray\n");
	list->peep(list);
	list->repr(list);
	printf("\n");

	printf("Test insert(OUT_OF_RANGE_INDEX)\n");
	list->insert(list, 50000, gc_strdup("OUT_OF_RANGE_INDEX test", gc), gc);
	list->repr(list);
	printf("\n");

	printf("Test insert(NEGATIVE_INDEX)\n");
	list->insert(list, -5, gc_strdup("NEGATIVE_INDEX test", gc), gc);
	list->repr(list);
	printf("\n");

	printf("Push 4 strs to list\n");
	list->push(list, gc_strdup("Hello", gc), gc);
	list->push(list, gc_strdup("World", gc), gc);
	list->push(list, gc_strdup("Mine", gc), gc);
	list->push(list, gc_strdup("Craft", gc), gc);
	list->repr(list);
	printf("\n");

	printf("Test peep()\n");
	printf("Peep result: %s\n", (char *)list->peep(list));
	list->repr(list);
	printf("\n");

	printf("Test pop()\n");
	list->pop(list);
	list->repr(list);
	printf("\n");

	printf("Test pop_i(1)\n");
	list->pop_i(list, 1);
	list->repr(list);
	printf("\n");

	printf("Test pop_i(OUT_OF_RANGE_INDEX)\n");
	list->pop_i(list, 5000);
	list->repr(list);
	printf("\n");

	printf("Test pop_i(NEGATIVE_INDEX)\n");
	list->pop_i(list, -50000);
	list->repr(list);
	printf("\n");
}

int	main(void)
{
	t_gc	*gc;
	gc = init_gc();
	test_darray(gc);
	gc->clean(gc);
	return (0);
}
*/
