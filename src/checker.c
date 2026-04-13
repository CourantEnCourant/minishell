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
					return (false);
				open_paren_count--;
			}
		}
		i++;
	}
	return (state == TEXT && open_paren_count == 0);
}

bool	is_valid_tree(t_btree *ast)
{
	t_token	*current;

	if (!ast || !ast->value)
		return (false);
	current = ast->value;
	if (current->type == CMD)
		return (!ast->left && !ast->right);
	else if (current->type == SUBSHELL)
		return (is_valid_tree(ast->left) && !ast->right);
	else if (current->type == CLOSE_PAREN)
		return (false);
	else
		return (is_valid_tree(ast->left) && is_valid_tree(ast->right));
}
