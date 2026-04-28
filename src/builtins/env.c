/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 23:40:06 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/28 23:42:42 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_libft.h"
#include "minishell.h"

t_env	*init_env(t_gc *gc)
{
	t_env	*env;

	env = gc_malloc(sizeof(t_env), gc);
	env->cwd = gc_getcwd(gc);
	return (env);
}
