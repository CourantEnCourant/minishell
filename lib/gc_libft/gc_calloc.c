/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:03:09 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/03 13:25:52 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_libft.h"

void	*gc_calloc(size_t nmemb, size_t size, t_gc *gc)
{
	void	*arr;
	int		total_size;

	total_size = nmemb * size;
	if (size && (total_size / size != nmemb))
		return (NULL);
	arr = gc_malloc(nmemb * size, gc);
	ft_bzero(arr, nmemb * size);
	return (arr);
}
