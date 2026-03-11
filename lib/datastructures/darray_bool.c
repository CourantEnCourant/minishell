/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_bool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:39:56 by weiqi             #+#    #+#             */
/*   Updated: 2026/02/03 13:21:23 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "datastructures.h"

bool	is_sorted(t_darray *self)
{
	size_t	i;

	i = 0;
	while (i < self->len - 1)
	{
		if (self->arr[i + 1] > self->arr[i])
			return (false);
		i++;
	}
	return (true);
}
