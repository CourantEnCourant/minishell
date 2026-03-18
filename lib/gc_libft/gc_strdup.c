/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:24:25 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/15 22:22:41 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gc_libft.h"

char	*gc_strdup(char *s, t_gc *gc)
{
	char	*s_dup;

	s_dup = ft_strdup(s);
	if (!s_dup)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, s_dup);
	return (s_dup);
}
