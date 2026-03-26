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

#include <assert.h>
#include <string.h>
#include "libft.h"
#include "gc_libft.h"
#include "datastructures.h"

static void	repr_str(void *value)
{
	ft_printf("%s", (char *)value);
}

void	test_darray(t_gc *gc)
{
	t_darray	*list;

	ft_printf("==========darray test==========\n");
	list = init_darray(gc);

	ft_printf("Test empty darray\n");
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test pop() from empty darray\n");
	assert(list->pop(list) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test pop_i() from empty darray\n");
	assert(list->pop_i(list, 1) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peep() from empty darray\n");
	assert(list->peep(list) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test insert(OUT_OF_RANGE_INDEX)\n");
	list->insert(list, 50000, gc_strdup("OUT_OF_RANGE_INDEX test", gc));
	assert(list->len == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test insert(NEGATIVE_INDEX)\n");
	list->insert(list, -5, gc_strdup("NEGATIVE_INDEX test", gc));
	assert(list->len == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Push 4 strs to list\n");
	list->push(list, gc_strdup("Hello", gc));
	list->push(list, gc_strdup("World", gc));
	list->push(list, gc_strdup("Mine", gc));
	list->push(list, gc_strdup("Craft", gc));
	assert(list->len == 4);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peep() returns last element\n");
	assert(strcmp((char *)list->peep(list), "Craft") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test pop()\n");
	assert(strcmp((char *)list->pop(list), "Craft") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test pop_i(1)\n");
	assert(strcmp((char *)list->pop_i(list, 1), "World") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test pop_i(OUT_OF_RANGE_INDEX)\n");
	assert(list->pop_i(list, 5000) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test pop_i(NEGATIVE_INDEX)\n");
	assert(list->pop_i(list, -50000) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");
}

int	main(void)
{
	t_gc	*gc;

	gc = init_gc();
	test_darray(gc);
	gc->clean(gc);
	return (0);
}
