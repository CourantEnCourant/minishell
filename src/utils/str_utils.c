/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 23:55:28 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/01 23:56:37 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "libft.h"

bool	strs_eq(void *s1, void *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}

bool	startswith(void *s, void *ref)
{
	return (ft_strncmp(s, ref, ft_strlen(ref)) == 0);
}

bool	str_is_num(char *s)
{
	size_t	i;
	
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	int64_overflow(char *n)
{
	uint64_t	result;
	uint64_t	limit;
	size_t		i;

	result = 0;
	limit = INT64_MAX;
	i = 0;
	while (ft_isspace(n[i]))
		i++;
	if (n[i] == '+' || n[i] == '-')
	{
		if (n[i] == '-')
			limit = (uint64_t)INT64_MIN;
		i++;
	}
	while (n[i])
	{
		result = result * 10 + (n[i] - '0');
		if (result > limit)
			return (true);
		i++;
	}
	return (false);
}
