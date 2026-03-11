/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:19:52 by weiqi             #+#    #+#             */
/*   Updated: 2026/02/06 13:39:05 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdarg.h>
#include "libft.h"

int	parse_arg(char placeholder, va_list *list);

static int	norminette(const char *s, va_list *args_ptr, size_t i, int count)
{
	int	substr_count;

	while (s[i])
	{
		if (s[i] == '%')
		{
			substr_count = parse_arg(s[i + 1], args_ptr);
			if (substr_count < 0)
				return (-1);
			count += substr_count;
			i += 2;
			continue ;
		}
		ft_putchar_fd(s[i], 1);
		i++;
		count++;
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		count;
	va_list	args;

	va_start(args, s);
	count = norminette(s, &args, 0, 0);
	va_end(args);
	return (count);
}
