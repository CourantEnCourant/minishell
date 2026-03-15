/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:24:25 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/15 19:25:05 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gc_libft.h"

void	*gc_strdup(char *s, t_gc *gc)
{
	void	*s_dup;

	s_dup = ft_strdup(s);
	if (!s_dup)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, s_dup);
	return (s_dup);
}
