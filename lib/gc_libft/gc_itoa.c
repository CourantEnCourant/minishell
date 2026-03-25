/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:39:55 by anying            #+#    #+#             */
/*   Updated: 2026/03/25 18:42:23 by anying           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_libft.h"

static int	get_len(int n)
{
	int	len;

	len = (n <= 0) ? 1 : 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*gc_itoa(int n, t_gc *gc)
{
	char			*str;
	int				len;
	unsigned int	num;

	len = get_len(n);
	str = gc_malloc(len + 1, gc); // 使用你的 GC 内存分配
	str[len] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (num != 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}