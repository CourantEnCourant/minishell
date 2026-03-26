/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:31:04 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/03/24 19:44:56 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "gc_libft.h"
#include "datastructures.h"

void	*peek(t_darray *self)
{
	if (self->len == 0)
	{
		ft_printf("IndexError: peeked from empty darray\n");
		return (NULL);
	}
	return (self->arr[self->len - 1]);
}

void	insert(t_darray *s, size_t i, void *item)
{
	void	**arr_ext;

	if (i > s->len)
	{
		ft_printf("IndexError: max len is %d, insert at %d\n", s->len, i);
		return ;
	}
	if (s->len >= s->capacity)
	{
		s->capacity *= 2;
		arr_ext = gc_calloc(s->capacity + 1, sizeof(void *), s->gc);
		ft_memmove(arr_ext, s->arr, s->len * sizeof(void *));
		s->arr = arr_ext;
	}
	ft_memmove(&s->arr[i + 1], &s->arr[i], (s->len - i) * sizeof(void *));
	s->arr[i] = item;
	s->len++;
}

void	push(t_darray *self, void *item)
{
	self->insert(self, self->len, item);
}

void	*pop_i(t_darray *s, size_t i)
{
	void	*item;

	if (s->len == 0)
	{
		ft_printf("IndexError: popped from empty darray\n");
		return (NULL);
	}
	if (i > s->len - 1)
	{
		ft_printf("IndexError: max index %d, popped at %d\n", s->len - 1, i);
		return (NULL);
	}
	item = s->arr[i];
	ft_memmove(&s->arr[i], &s->arr[i + 1], (s->len - i) * sizeof(void *));
	s->len--;
	return (item);
}

void	*pop(t_darray *self)
{
	if (self->len == 0)
	{
		ft_printf("IndexError: popped from empty darray\n");
		return (NULL);
	}
	return (self->pop_i(self, self->len - 1));
}
