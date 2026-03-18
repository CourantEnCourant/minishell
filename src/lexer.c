/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 17:39:15 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/17 17:40:58 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "minishell.h"

static t_lexer_state	update_state(char c, t_lexer_state current_state)
{
	if (current_state == TEXT)
	{
		if (c == '\'')
			return (SINGLE);
		else if (c == '"')
			return (DOUBLE);
	}
	else if (current_state == SINGLE && c == '\'')
		return (TEXT);
	else if (current_state == DOUBLE && c == '"')
		return (TEXT);
	return (current_state);
}

bool	is_valid_cmd(char *cmd)
{
	size_t			i;
	t_lexer_state	state;
	int				open_paren_count;

	i = 0;
	state = TEXT;
	open_paren_count = 0;
	while (cmd[i])
	{
		state = update_state(cmd[i], state);
		if (state == TEXT)
		{
			if (cmd[i] == '(')
				open_paren_count++;
			else if (cmd[i] == ')')
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

static size_t	process(t_darray *tokens, char *cmd, int len, char *operator)
{
	char	*token;

	token = gc_substr(cmd, 0, len, tokens->gc);
	token = gc_strtrim(token, " ", tokens->gc);
	if (token[0])
		tokens->push(tokens, token);
	if (operator[0])
		tokens->push(tokens, operator);
	return (len + ft_strlen(operator));
}

static size_t	lookup(t_darray *tokens, char *cmd, size_t start, size_t i)
{
	if (cmd[i] == '&' && cmd[i + 1] == '&')
		start += process(tokens, &cmd[start], i - start, "&&");
	else if (cmd[i] == '|')
		start += process(tokens, &cmd[start], i - start, "|");
	return (start);
}

t_darray	*tokenize(char *cmd, t_gc *gc)
{
	t_darray		*tokens;
	t_lexer_state	state;
	size_t			i;
	size_t			start;

	tokens = init_darray(gc);
	state = TEXT;
	i = 0;
	start = 0;
	while (cmd[i])
	{
		if (i < start)
			i = start;
		state = update_state(cmd[i], state);
		if (state == SINGLE || state == DOUBLE)
		{
			i++;
			continue ;
		}
		start = lookup(tokens, cmd, start, i);
		i++;
	}
	process(tokens, &cmd[start], i - start, "");
	return (tokens);
}
