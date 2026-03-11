/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:03:21 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/02/03 13:10:31 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gc_libft.h"

void	*gc_malloc(size_t size, t_gc *gc)
{
	void	*memory;

	memory = malloc(size);
	if (!memory)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, memory);
	return (memory);
}
