/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 20:12:32 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/02 21:34:49 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "gc_libft.h"
#include "datastructures.h"

void	test_darray(t_gc *gc)
{
	t_darray	*list;

	list = init_darray(gc);
	list->push(list, gc_strdup("Hello", gc), gc);
	list->push(list, gc_strdup("World", gc), gc);
	list->repr(list);
}

int	main(void)
{
	t_gc	*gc;
	gc = init_gc();
	test_darray(gc);
	gc->clean(gc);
	return (0);
}
