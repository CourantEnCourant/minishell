/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:54:06 by fdong             #+#    #+#             */
/*   Updated: 2026/05/18 16:23:32 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"

size_t	len(void **arr);
bool	key_match(void *envar, void *str);

static char	*cd_path(char *path, t_env *env)
{
	char	*oldpwd;
	t_envar	*pwd_var;
	char	*newpwd;

	pwd_var = env->envp->find(env->envp, key_match, "PWD");
	if (pwd_var && pwd_var->value)
		oldpwd = pwd_var->value;
	else
		oldpwd = "";
	if (chdir(path) == -1)
	{
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		env->exit_code = 1;
		return (NULL);
	}
	newpwd = gc_getcwd(env->gc);
	if (!newpwd)
	{
		perror("cd");
		newpwd = "";
	}
	env->set_envar(env, "OLDPWD", oldpwd);
	env->set_envar(env, "PWD", newpwd);
	env->exit_code = 0;
	return (newpwd);
}

static void	cd_dash(t_env *env)
{
	t_envar	*oldpwd_var;
	char	*path;

	oldpwd_var = env->envp->find(env->envp, key_match, "OLDPWD");
	if (oldpwd_var && oldpwd_var->value)
	{
		path = cd_path(oldpwd_var->value, env);
		if (path)
			printf("%s\n", path);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "cd: OLDPWD not set\n");
		env->exit_code = 1;
		return ;
	}
}

static void	cd_home(t_env *env)
{
	t_envar	*home_var;

	home_var = env->envp->find(env->envp, key_match, "HOME");
	if (home_var && home_var->value)
		cd_path(home_var->value, env);
	else
	{
		ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
		env->exit_code = 1;
		return ;
	}
}

void	cd(char **options, t_env *env)
{
	if (len((void **)options) == 1)
	{
		cd_home(env);
		return ;
	}
	if (len((void **)options) > 2)
	{
		ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		env->exit_code = 1;
		return ;
	}
	if (ft_strcmp(options[1], "-") == 0)
		cd_dash(env);
	else
		cd_path(options[1], env);
}
