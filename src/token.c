/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:04:44 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/18 17:15:36 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static void	match_binding_power(t_token *token)
{
	if (token->type == OR)
	{
		token->bind_left = 11;
		token->bind_right = 10;
	}
	else if (token->type == AND)
	{
		token->bind_left = 21;
		token->bind_right = 20;
	}
	else if (token->type == PIPE)
	{
		token->bind_left = 31;
		token->bind_right = 30;
	}
	else
	{
		token->bind_left = 0;
		token->bind_right = 0;
	}
}

static void	repr(t_token *self)
{
	printf("value: %s\n", self->value);
	if (self->type == AND)
		printf("type: AND\n");
	if (self->type == OR)
		printf("type: OR\n");
	if (self->type == PIPE)
		printf("type: PIPE\n");
	if (self->type == SUBSHELL)
		printf("type: SUBSHELL\n");
	if (self->type == CLOSE_PAREN)
		printf("type: CLOSE_PAREN\n");
	if (self->type == OPERAND)
		printf("type: OPERAND\n");
}

t_token	*init_token(char *value, t_gc *gc)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), gc);
	token->value = value;
	if (ft_strcmp(value, "&&") == 0)
		token->type = AND;
	else if (ft_strcmp(value, "||") == 0)
		token->type = OR;
	else if (ft_strcmp(value, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(value, "(") == 0)
		token->type = SUBSHELL;
	else if (ft_strcmp(value, ")") == 0)
		token->type = CLOSE_PAREN;
	else
		token->type = OPERAND;
	match_binding_power(token);
	token->repr = repr;
	return (token);
}
