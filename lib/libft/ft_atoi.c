/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:37:46 by weizhang          #+#    #+#             */
/*   Updated: 2025/11/15 15:57:36 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

static bool	ft_isspace(char a)
{
	if (a == '\f' || a == '\n' || a == '\r')
		return (true);
	if (a == ' ' || a == '\t' || a == '\v')
		return (true);
	return (false);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		result;
	int		is_neg;

	i = 0;
	result = 0;
	is_neg = -1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			is_neg *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 - (nptr[i] - '0');
		i++;
	}
	return (is_neg * result);
}

/*
#include <stdio.h>
int	main(int argc, char *argv[])
{
	printf("%d\n", ft_atoi(argv[1]));
}
*/
