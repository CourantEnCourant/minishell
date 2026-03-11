/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:23:34 by weizhang          #+#    #+#             */
/*   Updated: 2025/11/13 03:07:34 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*
#include <stdio.h>
#include <unistd.h>
int	main(void)
{
	char str[100] = "Hello this is a test string.\n";
	ft_bzero(str + 5, sizeof(char) * 5);
	for (int i = 0; i < 100; i++)
	{
		if (str[i] == '\0')
		{
			write(1, "d", 1);
			continue;
		}
		write(1, str + i, 1);
	}
	return (0);
}
*/
