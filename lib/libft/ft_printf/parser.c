/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:41:28 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/12/02 10:29:04 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdbool.h>
#include "libft.h"

int	parse_char(char a);
int	parse_str(char *s);
int	parse_int(int n);
int	parse_pointer(void *ptr);
int	parse_unsigned_int(unsigned int n);
int	parse_unsigned_hex(unsigned int n, bool upper);

int	parse_arg(char arg, va_list *args)
{
	if (arg == 'c')
		return (parse_char(va_arg(*args, int)));
	if (arg == 's')
		return (parse_str(va_arg(*args, char *)));
	if (arg == 'p')
		return (parse_pointer(va_arg(*args, void *)));
	if (arg == 'd' || arg == 'i')
		return (parse_int(va_arg(*args, int)));
	if (arg == 'u')
		return (parse_unsigned_int(va_arg(*args, unsigned int)));
	if (arg == 'x')
		return (parse_unsigned_hex(va_arg(*args, unsigned int), false));
	if (arg == 'X')
		return (parse_unsigned_hex(va_arg(*args, unsigned int), true));
	if (arg == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	return (-1);
}
