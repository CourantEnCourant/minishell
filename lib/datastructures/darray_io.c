/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:31:04 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/02/03 13:23:30 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "gc_libft.h"
#include "datastructures.h"

int	peep(t_darray *self)
{
	return (self->arr[self->len - 1]);
}

void	insert(t_darray *self, size_t i, int num, t_gc *gc)
{
	int	*arr_extended;

	if (self->len && self->len % LIST_LEN == 0)
	{
		arr_extended = gc_calloc(self->len * 2 + 1, sizeof(int), gc);
		ft_memmove(arr_extended, self->arr, self->len * sizeof(int));
		self->arr = arr_extended;
	}
	ft_memmove(&self->arr[i + 1], &self->arr[i], (self->len - i) * sizeof(int));
	self->arr[i] = num;
	self->len++;
}

void	push(t_darray *self, int num, t_gc *gc)
{
	self->insert(self, self->len, num, gc);
}

int	pop_i(t_darray *self, size_t i)
{
	int	num;

	if (self->len == 0)
	{
		ft_printf("Popped from empty darray\n");
		return (0);
	}
	num = self->arr[i];
	ft_memmove(&self->arr[i], &self->arr[i + 1], (self->len - i) * sizeof(int));
	self->len--;
	return (num);
}

int	pop(t_darray *self)
{
	return (self->pop_i(self, self->len - 1));
}
