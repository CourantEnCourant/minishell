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

bool	unmatched_parenthesis(t_env *env)
{
	ft_dprintf(STDERR_FILENO,
		"syntax error with unmatched parenthesis\n");
	env->exit_code = 2;
	return (false);
}

static bool	unmatched_quotes(t_env *env)
{
	ft_dprintf(STDERR_FILENO,
		"syntax error with unmatched quotes\n");
	env->exit_code = 2;
	return (false);
}

bool	check_unmatched(t_lexer_state state, int open_paren_count, t_env *env)
{
	if (state != TEXT)
		return (unmatched_quotes(env));
	if (open_paren_count != 0)
		return (unmatched_parenthesis(env));
	return (true);
}
