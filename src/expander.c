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
#include "libft.h"
#include "minishell.h"

bool	key_match(void *envar, void *str);
void	*gc_strjoin_wrap(void *s1, void *s2, t_gc *gc);

char	*find_var(char *key, t_env *env)
{
	t_envar	*envar;

	envar = env->envp->find(env->envp, key_match, key);
	if (!envar)
		return ("");
	return (envar->to_str(envar));
}

char	*expand_arg(char *arg, t_env *env)
{
	t_dfa_state	state;
	t_dfa_state	previous;
	t_darray	*fragments;
	size_t		i;
	size_t		start;

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
			else if (arg[i] == '$')
			{
				previous = state;
				state = DOLLAR;
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
			else if (arg[i] == '$')
			{
				previous = state;
				state = DOLLAR;
				fragments->push(fragments, gc_substr(arg, start, i - start, env->gc));
				start = i + 1;
			}
		}
		else if (state == DOLLAR)
		{
			if (arg[i] == '?')
			{
				fragments->push(fragments, gc_itoa(env->exit_code, env->gc));
				state = previous;
				start = i + 1;
			}
			else if (ft_isalpha(arg[i]) || arg[i] == '_')
				state = ALPHA;
			else
			{
				fragments->push(fragments, "$");
				state = previous;
				start = i;
				continue ;
			}
		}
		else if (state == ALPHA)
		{
			if (!ft_isalnum(arg[i]) && arg[i] != '_')
			{
				fragments->push(fragments, find_var(gc_substr(arg, start, i - start, env->gc), env));
				state = previous;
				start = i;
				continue ;
			}
		}
		i++;
	}
	if (state == DOLLAR)
		fragments->push(fragments, "$");
	else if (state == ALPHA)
		fragments->push(fragments, find_var(gc_substr(arg, start, i - start, env->gc), env));
	else
		fragments->push(fragments, gc_substr(arg, start, i - start, env->gc));
	return (fragments->reduce(fragments, gc_strjoin_wrap, ""));
}

void	expand_cmd(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	size_t	i;

	i = 0;
	while (i < cmd->argv->len)
	{
		cmd->argv->set(cmd->argv, i,
			expand_arg(cmd->argv->peek_i(cmd->argv, i), env));
		i++;
	}
	i = 0;
	while (i < cmd->redirs->len)
	{
		redir = cmd->redirs->peek_i(cmd->redirs, i);
		redir->set_filename(redir, expand_arg(redir->filename, env));
		i++;
	}
}
