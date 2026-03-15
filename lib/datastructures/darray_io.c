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

void	*peep(t_darray *self)
{
	return (self->arr[self->len - 1]);
}

void	insert(t_darray *self, size_t i, void *item, t_gc *gc)
{
	void	**arr_extended;

	if (i > self->len)
		i = self->len;
	if (self->len == self->capacity)
	{
		arr_extended = gc_calloc(self->capacity * 2 + 1, sizeof(void *), gc);
		ft_memmove(arr_extended, self->arr, self->capacity * sizeof(void *));
		self->arr = arr_extended;
		self->capacity = self->capacity * 2;
	}
	ft_memmove(&self->arr[i + 1], &self->arr[i], (self->len - i) * sizeof(void *));
	self->arr[i] = item;
	self->len++;
}

void	push(t_darray *self, void *item, t_gc *gc)
{
	self->insert(self, self->len, item, gc);
}

void	*pop_i(t_darray *self, size_t i)
{
	void	*item;

	if (self->len == 0)
	{
		ft_printf("Popped from empty darray\n");
		return (NULL);
	}
	item = self->arr[i];
	ft_memmove(&self->arr[i], &self->arr[i + 1], (self->len - i) * sizeof(void *));
	self->len--;
	return (item);
}

void	*pop(t_darray *self)
{
	return (self->pop_i(self, self->len - 1));
}
