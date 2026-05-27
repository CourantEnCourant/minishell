/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 00:00:00 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/26 00:00:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"
#include "minishell.h"

char	*find_var(char *key, t_env *env);

static bool	handle_text(char *arg, t_exp *e, t_env *env)
{
	if (arg[e->i] == '\'' || arg[e->i] == '"')
	{
		if (arg[e->i] == '\'')
			e->state = SINGLE;
		else
			e->state = DOUBLE;
		e->fragments->push(e->fragments,
			gc_substr(arg, e->start, e->i - e->start, env->gc));
		e->fragments->push(e->fragments, SENTINEL_STR);
		e->start = e->i + 1;
	}
	else if (arg[e->i] == '$')
	{
		e->previous = e->state;
		e->state = DOLLAR;
		e->fragments->push(e->fragments,
			gc_substr(arg, e->start, e->i - e->start, env->gc));
		e->start = e->i + 1;
	}
	return (false);
}

static bool	handle_quote(char *arg, t_exp *e, t_env *env)
{
	if (e->state == SINGLE && arg[e->i] == '\'')
	{
		e->state = TEXT;
		e->fragments->push(e->fragments,
			gc_substr(arg, e->start, e->i - e->start, env->gc));
		e->fragments->push(e->fragments, SENTINEL_STR);
		e->start = e->i + 1;
	}
	else if (e->state == DOUBLE && arg[e->i] == '"')
	{
		e->state = TEXT;
		e->fragments->push(e->fragments,
			gc_substr(arg, e->start, e->i - e->start, env->gc));
		e->fragments->push(e->fragments, SENTINEL_STR);
		e->start = e->i + 1;
	}
	else if (e->state == DOUBLE && arg[e->i] == '$')
	{
		e->previous = e->state;
		e->state = DOLLAR;
		e->fragments->push(e->fragments,
			gc_substr(arg, e->start, e->i - e->start, env->gc));
		e->start = e->i + 1;
	}
	return (false);
}

static bool	handle_dollar(char *arg, t_exp *e, t_env *env)
{
	if (arg[e->i] == '?')
	{
		e->fragments->push(e->fragments,
			gc_itoa(env->exit_code, env->gc));
		e->state = e->previous;
		e->start = e->i + 1;
	}
	else if (ft_isdigit(arg[e->i]))
	{
		e->state = e->previous;
		e->start = e->i + 1;
	}
	else if (ft_isalpha(arg[e->i]) || arg[e->i] == '_')
		e->state = ALPHA;
	else
	{
		e->fragments->push(e->fragments, "$");
		e->state = e->previous;
		e->start = e->i;
		return (true);
	}
	return (false);
}

static bool	handle_alpha(char *arg, t_exp *e, t_env *env)
{
	if (!ft_isalnum(arg[e->i]) && arg[e->i] != '_')
	{
		e->fragments->push(e->fragments,
			find_var(gc_substr(arg, e->start,
					e->i - e->start, env->gc), env));
		e->state = e->previous;
		e->start = e->i;
		return (true);
	}
	return (false);
}

bool	dispatch(char *arg, t_exp *e, t_env *env)
{
	if (e->state == TEXT)
		return (handle_text(arg, e, env));
	if (e->state == SINGLE || e->state == DOUBLE)
		return (handle_quote(arg, e, env));
	if (e->state == DOLLAR)
		return (handle_dollar(arg, e, env));
	if (e->state == ALPHA)
		return (handle_alpha(arg, e, env));
	return (false);
}
