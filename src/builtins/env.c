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

void pwd(char **options, t_env *env);

int	exec_builtins(char *cmd, char **options, t_env *env)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		pwd(options, env);
	return (env->exit_code);
}

t_darray	*init_builtins(t_gc *gc)
{
	t_darray	*builtins;

	builtins = init_darray(gc);
	builtins->push(builtins, ft_strdup("pwd"));
	return (builtins);
}

t_env	*init_env(t_gc *gc)
{
	t_env		*env;
	extern char	**environ;

	env = gc_malloc(sizeof(t_env), gc);
	env->exit_code = 0;
	env->cwd = gc_getcwd(gc);
	env->builtins = init_builtins(gc);
	env->envp = init_from_arr((void **)environ, gc);
	return (env);
}
