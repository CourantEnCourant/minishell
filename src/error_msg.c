/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 22:52:57 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/20 23:02:08 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

bool	unmatched_parenthesis(void)
{
	ft_dprintf(STDERR_FILENO,
		"syntax error with unmatched parenthesis\n");
	return (false);
}

static bool	unmatched_quotes(void)
{
	ft_dprintf(STDERR_FILENO,
		"syntax error with unmatched quotes\n");
	return (false);
}

bool	check_unmatched(t_lexer_state state, int open_paren_count)
{
	if (state != TEXT)
		return (unmatched_quotes());
	if (open_paren_count != 0)
		return (unmatched_parenthesis());
	return (true);
}
