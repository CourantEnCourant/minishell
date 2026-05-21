/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 23:40:06 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/11 22:01:31 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

void	cd(char **options, t_env *env);
void	echo(char **options, t_env *env);
void	exit_minishell(char **options, t_env *env);
void	export(char **options, t_env *env);
bool	key_match(void *envar, void *str);
void	pwd(char **options, t_env *env);
void	unset(char **options, t_env *env);

void	print_env(char **options, t_env *env)
{
	t_envar	*envar;
	size_t	i;

	(void)options;
	i = 0;
	while (i < env->envp->len)
	{
		envar = env->envp->peek_i(env->envp, i);
		if (envar->exported)
			printf("%s=%s\n", envar->key, envar->value);
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
	else if (ft_strcmp(cmd, "echo") == 0)
		echo(options, env);
	else if (ft_strcmp(cmd, "export") == 0)
		export(options, env);
	else if (ft_strcmp(cmd, "cd") == 0)
		cd(options, env);
}

t_darray	*init_builtins(t_gc *gc)
{
	t_darray	*builtins;

	builtins = init_darray(gc);
	builtins->push(builtins, "pwd");
	builtins->push(builtins, "export");
	builtins->push(builtins, "exit");
	builtins->push(builtins, "env");
	builtins->push(builtins, "unset");
	builtins->push(builtins, "echo");
	builtins->push(builtins, "cd");
	return (builtins);
}

static char	**export_envp(t_env *self)
{
	char	**envp;
	t_envar	*var;
	size_t	i;
	size_t	j;

	envp = gc_calloc(self->envp->len + 1, sizeof(char *), self->gc);
	i = 0;
	j = 0;
	while (i < self->envp->len)
	{
		var = self->envp->peek_i(self->envp, i);
		if (var->exported)
		{
			envp[j] = var->to_str(var);
			j++;
		}
		i++;
	}
	return (envp);
}

static void	set_envar(t_env *self, char *key, char *value)
{
	t_envar	*envar;

	envar = self->envp->find(self->envp, key_match, key);
	if (envar)
		envar->value = value;
	else
		self->envp->push(self->envp, init_envar(key, value, true, self->gc));
}

t_env	*init_env(t_gc *gc)
{
	t_env		*env;
	extern char	**environ;
	size_t		i;

	env = gc_malloc(sizeof(t_env), gc);
	env->exit_code = 0;
	env->builtins = init_builtins(gc);
	env->envp = init_darray(gc);
	i = 0;
	while (environ[i])
	{
		env->envp->push(env->envp, init_envar_from_str(environ[i], gc));
		i++;
	}
	env->gc = gc;
	env->export_envp = export_envp;
	env->set_envar = set_envar;
	return (env);
}
