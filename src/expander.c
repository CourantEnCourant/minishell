/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 18:48:47 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/10 19:07:47 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "datastructures.h"
#include "minishell.h"

void	*gc_strjoin_wrap(void *s1, void *s2, t_gc *gc);

char	*expand_arg(char *arg, t_env *env)
{
	t_lexer_state	state;
	t_darray		*fragments;
	size_t			i;
	size_t			start;

	fragments = init_darray(env->gc);
	state = TEXT;
	i = 0;
	start = 0;
	while (arg[i])
	{
		if (state == TEXT)
		{
			if (arg[i] == '\'')
			{
				state = SINGLE;
				fragments->push(fragments, gc_substr(arg, start, i - start, env->gc));
				start = i + 1;
			}
			else if (arg[i] == '"')
			{
				state = DOUBLE;
				fragments->push(fragments, gc_substr(arg, start, i - start, env->gc));
				start = i + 1;
			}
		}
		else if (state == SINGLE)
		{
			if (arg[i] == '\'')
			{
				state = TEXT;
				fragments->push(fragments, gc_substr(arg, start, i - start, env->gc));
				start = i + 1;
			}
		}
		else if (state == DOUBLE)
		{
			if (arg[i] == '"')
			{
				state = TEXT;
				fragments->push(fragments, gc_substr(arg, start, i - start, env->gc));
				start = i + 1;
			}
		}
		i++;
	}
	fragments->push(fragments, gc_substr(arg, start, i - start, env->gc));
	return (fragments->reduce(fragments, gc_strjoin_wrap, ""));
}

void	expand_cmd(t_cmd *cmd, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < cmd->argv->len)
	{
		cmd->argv->set(cmd->argv, i,
				expand_arg(cmd->argv->peek_i(cmd->argv, i), env));
		i++;
	}
}

void	expand_ast(t_btree *ast, t_env *env)
{
	t_token	*token;

	token = ast->value;
	if (token->type == CMD)
		expand_cmd(token->cmd, env);
	else if (token->type == SUBSHELL)
		expand_ast(ast->left, env);
	else
	{
		expand_ast(ast->left, env);
		expand_ast(ast->right, env);
	}
}
