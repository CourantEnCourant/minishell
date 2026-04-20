/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 01:47:19 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/03 01:52:41 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

t_lexer_state	update_state(char c, t_lexer_state current_state);

bool	quotes_paren_match(char *input)
{
	size_t			i;
	t_lexer_state	state;
	int				open_paren_count;

	i = 0;
	state = TEXT;
	open_paren_count = 0;
	while (input[i])
	{
		state = update_state(input[i], state);
		if (state == TEXT)
		{
			if (input[i] == '(')
				open_paren_count++;
			else if (input[i] == ')')
			{
				if (open_paren_count == 0)
				{
					ft_dprintf(STDERR_FILENO,
							"syntax error with unmatched parenthesis\n");
					return (false);
				}
				open_paren_count--;
			}
		}
		i++;
	}
	if (open_paren_count != 0)
		ft_dprintf(STDERR_FILENO,
				"syntax error with unmatched parenthesis\n");
	if (state != TEXT)
		ft_dprintf(STDERR_FILENO,
				"syntax error with unmatched quotes\n");
	return (state == TEXT && open_paren_count == 0);
}
