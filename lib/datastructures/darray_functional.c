/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_functional.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:21:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/30 23:54:38 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdbool.h>
#include "datastructures.h"

bool	any(t_darray *s, bool (*pred)(void *elem, void *target), void *target)
{
	size_t	i;

	i = 0;
	while (i < s->len)
	{
		if (pred(s->peek_i(s, i), target))
			return (true);
		i++;
	}
	return (false);
}

void	*reduce(t_darray *s, void *(*f)(void *i1, void *i2, t_gc *gc), void *a)
{
	size_t	i;

	i = 0;
	while (i < s->len)
	{
		a = f(a, s->arr[i], s->gc);
		i++;
	}
	return (a);
}
