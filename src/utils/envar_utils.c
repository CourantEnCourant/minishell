/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:52:31 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/26 20:53:30 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
