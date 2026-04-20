/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 01:47:19 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/20 23:02:19 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_state	update_state(char c, t_lexer_state current_state);
bool			unmatched_parenthesis(void);
bool			check_unmatched(t_lexer_state state, int open_paren_count);

bool	quotes_paren_match(char *input)
{
	size_t			i;
	t_lexer_state	state;
	int				open_paren_count;

	i = -1;
	state = TEXT;
	open_paren_count = 0;
	while (input[++i])
	{
		state = update_state(input[i], state);
		if (state == TEXT)
		{
			if (input[i] == '(')
				open_paren_count++;
			else if (input[i] == ')')
			{
				if (open_paren_count == 0)
					return (unmatched_parenthesis());
				open_paren_count--;
			}
		}
	}
	return (check_unmatched(state, open_paren_count));
}
