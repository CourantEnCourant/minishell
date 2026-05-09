/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 23:40:06 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/30 21:18:58 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

t_env	*init_env(t_gc *gc)
{
	t_env		*env;
	extern char	**environ;

	env = gc_malloc(sizeof(t_env), gc);
	env->exit_code = 0;
	env->builtins = NULL;
	env->envp = init_from_arr((void **)environ, gc);
	env->gc = gc;
	return (env);
}
