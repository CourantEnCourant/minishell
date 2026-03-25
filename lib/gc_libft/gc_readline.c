/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hch <hch@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:18:22 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/25 18:29:39 by hch              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "gc_libft.h"

char	*gc_readline(const char *prompt, t_gc *gc)
{
	char	*line;
	line = readline(prompt);
	if (line)
	{
		gc->add(gc, line);
	}

	return (line);
}