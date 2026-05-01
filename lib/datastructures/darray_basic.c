/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:08:35 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/04/30 23:55:41 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "gc_libft.h"
#include "datastructures.h"

void	*peek_i(t_darray *self, size_t i);
void	*peek(t_darray *self);
void	insert(t_darray *self, size_t i, void *item);
void	push(t_darray *self, void *item);
void	*pop_i(t_darray *self, size_t i);
void	*pop(t_darray *self);
bool	any(t_darray *s, bool (*pred)(void *elem, void *target), void *target);
void	*reduce(t_darray *s, void *(*f)(void *i1, void *i2, t_gc *gc), void *a);

static void	**to_arr(t_darray *self)
{
	void	**arr;
	size_t	i;

	arr = gc_calloc(self->len + 1, sizeof(void *), self->gc);
	i = 0;
	while (i < self->len)
	{
		arr[i] = self->peek_i(self, i);
		i++;
	}
	return (arr);
}

static void	repr(t_darray *self, void (*repr_item)(void *value))
{
	size_t	i;

	write(1, "[", 1);
	i = 0;
	if (!self->len)
	{
		write(1, "]\n", 2);
		return ;
	}
	while (i < self->len - 1)
	{
		repr_item(self->arr[i]);
		write(1, ", ", 2);
		i++;
	}
	repr_item(self->arr[i]);
	write(1, "]\n", 2);
}

t_darray	*init_darray(t_gc *gc)
{
	t_darray	*darray;

	darray = gc_malloc(sizeof(t_darray), gc);
	darray->arr = gc_calloc((DARRAY_LEN + 1), sizeof(void *), gc);
	darray->len = 0;
	darray->capacity = DARRAY_LEN;
	darray->gc = gc;
	darray->repr = repr;
	darray->to_arr = to_arr;
	darray->peek_i = peek_i;
	darray->peek = peek;
	darray->insert = insert;
	darray->push = push;
	darray->pop_i = pop_i;
	darray->pop = pop;
	darray->any = any;
	darray->reduce = reduce;
	return (darray);
}

t_darray	*init_from_arr(void **arr, t_gc *gc)
{
	t_darray	*darray;
	size_t		i;

	darray = init_darray(gc);
	i = 0;
	while (arr[i])
	{
		darray->push(darray, arr[i]);
		i++;
	}
	return (darray);
}
