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

	ft_printf("Test peek() from empty darray\n");
	assert(list->peek(list) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek_i(0) from empty darray\n");
	assert(list->peek_i(list, 0) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek_i(5) from empty darray\n");
	assert(list->peek_i(list, 5) == NULL);
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

	ft_printf("Test peek() returns last element\n");
	assert(strcmp((char *)list->peek(list), "Craft") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek_i(0)\n");
	assert(strcmp((char *)list->peek_i(list, 0), "Hello") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek_i(1)\n");
	assert(strcmp((char *)list->peek_i(list, 1), "World") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek_i(2)\n");
	assert(strcmp((char *)list->peek_i(list, 2), "Mine") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek_i(3)\n");
	assert(strcmp((char *)list->peek_i(list, 3), "Craft") == 0);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek_i(OUT_OF_RANGE)\n");
	assert(list->peek_i(list, 100) == NULL);
	list->repr(list, repr_str);
	ft_printf("\n");

	ft_printf("Test peek() does not remove elements\n");
	list->peek(list);
	list->peek(list);
	assert(list->len == 4);
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

	ft_printf("Test pop/peek on empty does not change len\n");
	assert(list->len == 2);
	list->pop(list);
	list->pop(list);
	assert(list->len == 0);
	list->pop(list);
	list->pop_i(list, 0);
	list->peek(list);
	list->peek_i(list, 0);
	assert(list->len == 0);
	ft_printf("\n");

	ft_printf("Test len tracks push and pop correctly\n");
	list->push(list, gc_strdup("a", gc));
	assert(list->len == 1);
	list->push(list, gc_strdup("b", gc));
	assert(list->len == 2);
	list->push(list, gc_strdup("c", gc));
	assert(list->len == 3);
	list->pop(list);
	assert(list->len == 2);
	list->pop_i(list, 0);
	assert(list->len == 1);
	list->peek(list);
	assert(list->len == 1);
	list->peek_i(list, 0);
	assert(list->len == 1);
	list->pop(list);
	assert(list->len == 0);
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
