/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:40:48 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/17 17:46:45 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "gc_libft.h"
#include "minishell.h"

bool			is_valid_cmd(char *cmd);

t_parser	*init_parser(t_gc *gc)
{
	t_parser	*parser;

	parser = gc_malloc(sizeof(t_gc), gc);
	parser->is_valid_cmd = is_valid_cmd;
	return (parser);
}
