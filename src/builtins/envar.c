/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:49:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/16 16:30:46 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_libft.h"
#include "minishell.h"
#include <stdbool.h>

bool	envar_gt(void *e1, void *e2)
{
	t_envar	*envar1;
	t_envar	*envar2;

	envar1 = (t_envar *)e1;
	envar2 = (t_envar *)e2;
	return (ft_strcmp(envar1->key, envar2->key) > 0);
}

bool	key_match(void *envar, void *str)
{
	t_envar	*var;

	var = (t_envar *)envar;
	return (ft_strcmp(var->key, str) == 0);
}

char	*extract_key(char *envar, t_gc *gc)
{
	return (gc_substr(envar, 0, ft_strcspn(envar, "="), gc));
}

char	*extract_value(char *envar, t_gc *gc)
{
	char	*eq_ptr;

	eq_ptr = ft_strchr(envar, '=');
	if (!eq_ptr)
		return (NULL);
	return (gc_strdup(eq_ptr + 1, gc));
}

static char	*to_str(t_envar *self)
{
	char	*str;

	str = gc_strjoin(self->key, "=", self->gc);
	return (gc_strjoin(str, self->value, self->gc));
}

t_envar	*init_envar(char *key, char *value, bool exported, t_gc *gc)
{
	t_envar	*envar;

	envar = gc_malloc(sizeof(t_envar), gc);
	envar->key = key;
	envar->value = value;
	envar->exported = exported;
	envar->gc = gc;
	envar->to_str = to_str;
	return (envar);
}

t_envar	*init_envar_from_str(char *envar_str, t_gc *gc)
{
	char	*key;
	char	*value;

	key = extract_key(envar_str, gc);
	value = extract_value(envar_str, gc);
	return (init_envar(key, value, true, gc));
}

void	set_env_var(char *key, char *value, t_env *env)
{
	size_t	target_i;
	t_envar	*envar;

	target_i = env->envp->find_i(env->envp, key_match, key);
	if (target_i != env->envp->len)
	{
		envar = env->envp->peek_i(env->envp, target_i);
		envar->exported = true;
		envar->value = value;
	}
	else
		env->envp->push(env->envp, init_envar(key, value, true, env->gc));
}
