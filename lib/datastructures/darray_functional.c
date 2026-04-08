/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_functional.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:21:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/02 01:24:54 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"

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
