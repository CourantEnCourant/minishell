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

void	insert(t_darray *s, size_t i, int item, t_gc *gc)
{
	int	*arr_ext;

	if (s->len && s->len % LIST_LEN == 0)
	{
		arr_ext = gc_calloc(s->len * 2 + 1, sizeof(int), gc);
		ft_memmove(arr_ext, s->arr, s->len * sizeof(int));
		s->arr = arr_ext;
	}
	ft_memmove(&s->arr[i + 1], &s->arr[i], (s->len - i) * sizeof(int));
	s->arr[i] = item;
	s->len++;
}

void	push(t_darray *self, int item, t_gc *gc)
{
	self->insert(self, self->len, item, gc);
}

int	pop_i(t_darray *s, size_t i)
{
	int	item;

	if (s->len == 0)
	{
		ft_printf("Popped from empty darray\n");
		return (0);
	}
	item = s->arr[i];
	ft_memmove(&s->arr[i], &s->arr[i + 1], (s->len - i) * sizeof(int));
	s->len--;
	return (item);
}

int	pop(t_darray *self)
{
	return (self->pop_i(self, self->len - 1));
}
