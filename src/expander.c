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

#include "minishell.h"

bool	key_match(void *envar, void *str);
bool	strs_not_eq(void *s1, void *s2);
void	*gc_strjoin_wrap(void *s1, void *s2, t_gc *gc);
bool	dispatch(char *arg, t_exp *e, t_env *env);
void	*strip_sentinel(void *s, t_gc *gc);

char	*find_var(char *key, t_env *env)
{
	t_envar	*envar;

	envar = env->envp->find(env->envp, key_match, key);
	if (!envar || !envar->value)
		return ("");
	return (envar->value);
}

static char	*expand_tilde(char *arg, t_env *env)
{
	t_envar	*home;

	if (arg[0] != '~' || (arg[1] != '/' && arg[1] != '\0'))
		return (arg);
	home = env->envp->find(env->envp, key_match, "HOME");
	if (!home)
		return (arg);
	return (gc_strjoin(home->value, &arg[1], env->gc));
}

static char	*expand_arg(char *arg, t_env *env)
{
	t_exp	e;

	arg = expand_tilde(arg, env);
	e.fragments = init_darray(env->gc);
	e.state = TEXT;
	e.i = 0;
	e.start = 0;
	while (arg[e.i])
	{
		if (!dispatch(arg, &e, env))
			e.i++;
	}
	if (e.state == DOLLAR)
		e.fragments->push(e.fragments, "$");
	else if (e.state == ALPHA)
		e.fragments->push(e.fragments,
			find_var(gc_substr(arg, e.start, e.i - e.start, env->gc), env));
	else
		e.fragments->push(e.fragments,
			gc_substr(arg, e.start, e.i - e.start, env->gc));
	return (e.fragments->reduce(e.fragments, gc_strjoin_wrap, ""));
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
	cmd->set_argv(cmd, cmd->argv->filter(cmd->argv, strs_not_eq, ""));
	cmd->argv->for_each(cmd->argv, strip_sentinel);
	i = 0;
	while (i < cmd->redirs->len)
	{
		redir = cmd->redirs->peek_i(cmd->redirs, i);
		redir->set_filename(redir,
			strip_sentinel(expand_arg(redir->filename, env), env->gc));
		i++;
	}
}
