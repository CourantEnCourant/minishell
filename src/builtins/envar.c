/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 22:49:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/12 22:56:47 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_libft.h"
#include "minishell.h"
#include <stdbool.h>

bool	key_match(void *envar, void *str)
{
	t_envar	*var;

	var = (t_envar *)envar;
	return (ft_strcmp(var->key, str) == 0);
}

static char	*extract_key(char *envar, t_gc *gc)
{
	return (gc_substr(envar, 0, ft_strcspn(envar, "="), gc));
}

static char	*extract_value(char *envar, t_gc *gc)
{
	return (gc_strdup(ft_strchr(envar, '=') + 1, gc));
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
