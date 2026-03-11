/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:14:36 by weiqi             #+#    #+#             */
/*   Updated: 2025/11/14 13:21:28 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1_copy;
	const unsigned char	*s2_copy;

	s1_copy = s1;
	s2_copy = s2;
	i = 0;
	while (i < n)
	{
		if (s1_copy[i] != s2_copy[i])
			return (s1_copy[i] - s2_copy[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
int	main(void)
{
	char s1[] = "Hello world";
	char s2[] = "HellO world";

	printf("%d\n", ft_memcmp(s1, s2, sizeof(char) * ft_strlen(s1)));
}
*/
