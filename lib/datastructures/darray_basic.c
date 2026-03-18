/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:08:35 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/02/03 13:42:21 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "gc_libft.h"
#include "datastructures.h"

int		peep(t_darray *self);
void	insert(t_darray *s, size_t i, int item, t_gc *gc);
void	push(t_darray *self, int item, t_gc *gc);
int		pop_i(t_darray *s, size_t i);
int		pop(t_darray *self);
bool	is_sorted(t_darray *self);

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
		ft_printf("%d, ", self->arr[i]);
		i++;
	}
	ft_printf("%d", self->arr[i]);
	write(1, "]\n", 2);
}

t_darray	*init_darray(t_gc *gc)
{
	t_darray	*darray;

	darray = gc_malloc(sizeof(t_darray), gc);
	darray->arr = gc_calloc((LIST_LEN + 1), sizeof(int), gc);
	darray->len = 0;
	darray->repr = repr;
	darray->peep = peep;
	darray->insert = insert;
	darray->push = push;
	darray->pop_i = pop_i;
	darray->pop = pop;
	darray->is_sorted = is_sorted;
	return (darray);
}
