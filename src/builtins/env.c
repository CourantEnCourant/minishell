/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 23:40:06 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/09 20:05:09 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

void	pwd(char **options, t_env *env);
void	exit_minishell(char **options, t_env *env);
void	unset(char **options, t_env *env);

void	print_env(char **options, t_env *env)
{
	size_t	i;

	(void)options;
	i = 0;
	while (i < env->envp->len)
	{
		printf("%s\n", (char *)env->envp->peek_i(env->envp, i));
		i++;
	}
	env->exit_code = 0;
}

void	exec_builtins(char *cmd, char **options, t_env *env)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		pwd(options, env);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit_minishell(options, env);
	else if (ft_strcmp(cmd, "env") == 0)
		print_env(options, env);
	else if (ft_strcmp(cmd, "unset") == 0)
		unset(options, env);
}

t_darray	*init_builtins(t_gc *gc)
{
	t_darray	*builtins;

	builtins = init_darray(gc);
	builtins->push(builtins, "pwd");
	builtins->push(builtins, "exit");
	builtins->push(builtins, "env");
	builtins->push(builtins, "unset");
	return (builtins);
}

t_env	*init_env(t_gc *gc)
{
	t_env		*env;
	extern char	**environ;

	env = gc_malloc(sizeof(t_env), gc);
	env->exit_code = 0;
	env->builtins = init_builtins(gc);
	env->envp = init_from_arr((void **)environ, gc);
	env->gc = gc;
	return (env);
}
