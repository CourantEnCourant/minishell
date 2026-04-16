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

#include "libft.h"
#include "minishell.h"

void	repr_strs(char **strs);

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
		token->bind_left = 1;
		token->bind_right = 0;
	}
}

static void	repr(t_token *self)
{
	if (self->type == CMD)
		repr_strs(self->cmd->argv);
	else
		ft_printf("\"%s\"", self->value);
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
	else if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, ">>") == 0
		|| ft_strcmp(value, "<") == 0 || ft_strcmp(value, "<<") == 0)
		token->type = REDIR;
	else
		token->type = OPERAND;
	match_binding_power(token);
	token->repr = repr;
	return (token);
}

t_token *init_cmd_token(t_cmd *cmd, t_gc *gc)
{
	t_token	*token;

	token = gc_malloc(sizeof(t_token), gc);
	token->cmd = cmd;
	token->type = CMD;
	token->repr = repr;
	match_binding_power(token);
	return (token);
}
