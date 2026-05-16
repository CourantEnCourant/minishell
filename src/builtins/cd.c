/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:54:06 by fdong             #+#    #+#             */
/*   Updated: 2026/05/16 18:07:55 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	repr_strs(char **strs);
size_t	len(void **arr);
bool	key_match(void *envar, void *str);
void	set_env_var(char *key, char *value, t_env *env);

void	cd(char **options, t_env *env)
{
	char	*oldpwd;
	t_envar	*pwd_var;

	if (len((void **)options) == 1)
		return ;
	if (len((void **)options) > 2)
	{
		ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		env->exit_code = 1;
		return ;
	}
	pwd_var = env->envp->find(env->envp, key_match, "PWD");
	if (pwd_var && pwd_var->value)
		oldpwd = gc_strdup(pwd_var->value, env->gc);
	else
		oldpwd = gc_strdup("", env->gc);
	if (chdir(options[1]) == -1)
	{
		perror("cd");
		env->exit_code = 1;
		return ;
	}
	set_env_var(gc_strdup("OLDPWD", env->gc), oldpwd, env);
	set_env_var(gc_strdup("PWD", env->gc), gc_getcwd(env->gc), env);
	env->exit_code = 0;
}
