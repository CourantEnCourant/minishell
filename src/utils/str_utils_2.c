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
#include "minishell.h"

bool	strs_eq(void *s1, void *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}

bool	strs_not_eq(void *s1, void *s2)
{
	return (!strs_eq(s1, s2));
}

void	*gc_strdup_wrap(void *ref, t_gc *gc)
{
	return (gc_strdup(ref, gc));
}

bool	strs_lt(void *s1, void *s2)
{
	return (ft_strcmp(s1, s2) < 0);
}

void	*strip_sentinel(void *s, t_gc *gc)
{
	char	*str;
	char	*result;
	size_t	i;
	size_t	j;

	str = s;
	result = gc_malloc(ft_strlen(str) + 1, gc);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != SENTINEL)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
