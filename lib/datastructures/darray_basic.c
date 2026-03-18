/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:08:35 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/03/17 17:47:55 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "gc_libft.h"
#include "datastructures.h"

void	*peep(t_darray *self);
void	insert(t_darray *self, size_t i, void *item);
void	push(t_darray *self, void *item);
void	*pop_i(t_darray *self, size_t i);
void	*pop(t_darray *self);

static void	repr(t_darray *self)
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
		ft_printf("\"%s\", ", self->arr[i]);
		i++;
	}
	ft_printf("\"%s\"", self->arr[i]);
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
	darray->peep = peep;
	darray->insert = insert;
	darray->push = push;
	darray->pop_i = pop_i;
	darray->pop = pop;
	return (darray);
}
