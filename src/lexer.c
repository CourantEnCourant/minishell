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
#include "libft.h"
#include "datastructures.h"
#include "minishell.h"

t_lexer_state	update_state(char c, t_lexer_state current_state)
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

static size_t	process(t_darray *tokens, char *cmd, int len, char *operator)
{
	char	*token_value;
	t_token	*token;

	token_value = gc_substr(cmd, 0, len, tokens->gc);
	token_value = gc_strtrim(token_value, " ", tokens->gc);
	if (token_value[0])
	{
		token = init_token(token_value, tokens->gc);
		tokens->push(tokens, token);
	}
	if (operator && operator[0])
	{
		token = init_token(operator, tokens->gc);
		tokens->push(tokens, token);
		return (len + ft_strlen(operator));
	}
	else
		return (len);
}

static size_t	lookup(t_darray *tokens, char *cmd, size_t start, size_t i)
{
	if (cmd[i] == ' ')
		start += process(tokens, &cmd[start], i - start, NULL);
	else if (ft_strncmp(&cmd[i], "&&", 2) == 0)
		start += process(tokens, &cmd[start], i - start, "&&");
	else if (ft_strncmp(&cmd[i], "||", 2) == 0)
		start += process(tokens, &cmd[start], i - start, "||");
	else if (cmd[i] == '|' && cmd[i + 1] != '|')
		start += process(tokens, &cmd[start], i - start, "|");
	else if (cmd[i] == '(')
		start += process(tokens, &cmd[start], i - start, "(");
	else if (cmd[i] == ')')
		start += process(tokens, &cmd[start], i - start, ")");
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
	process(tokens, &cmd[start], i - start, NULL);
	return (tokens);
}
