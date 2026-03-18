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

void	insert(t_darray *s, size_t i, void *item, t_gc *gc)
{
	void	**arr_ext;

	if (s->len && s->len % LIST_LEN == 0)
	{
		arr_ext = gc_calloc(s->len * 2 + 1, sizeof(void *), gc);
		ft_memmove(arr_ext, s->arr, s->len * sizeof(void *));
		s->arr = arr_ext;
	}
	ft_memmove(&s->arr[i + 1], &s->arr[i], (s->len - i) * sizeof(void *));
	s->arr[i] = item;
	s->len++;
}

void	push(t_darray *self, void *item, t_gc *gc)
{
	self->insert(self, self->len, item, gc);
}

void	*pop_i(t_darray *s, size_t i)
{
	void	*item;

	if (s->len == 0)
	{
		ft_printf("Popped from empty darray\n");
		return (NULL);
	}
	item = s->arr[i];
	ft_memmove(&s->arr[i], &s->arr[i + 1], (s->len - i) * sizeof(void *));
	s->len--;
	return (item);
}

void	*pop(t_darray *self)
{
	return (self->pop_i(self, self->len - 1));
}
