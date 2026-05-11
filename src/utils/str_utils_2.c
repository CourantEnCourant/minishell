/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 23:01:40 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/11 23:02:38 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "gc_libft.h"

void	*gc_strdup_wrap(void *ref, t_gc *gc)
{
	return (gc_strdup(ref, gc));
}

bool	strs_lt(void *s1, void *s2)
{
	return (ft_strcmp(s1, s2) < 0);
}
