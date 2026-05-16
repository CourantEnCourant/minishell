/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 14:54:06 by fdong             #+#    #+#             */
/*   Updated: 2026/05/16 16:34:02 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	repr_strs(char **strs);
size_t	len(void **arr);
void	set_env_var(char *key, char *value, t_env *env);

void	cd(char **options, t_env *env)
{
	char	*oldpwd;

	if (len((void **)options) == 1)
		return ;
	if (len((void **)options) > 2)
	{
		ft_dprintf(STDERR_FILENO, "cd: too many arguments\n");
		env->exit_code = 1;
		return ;
	}
	oldpwd = gc_getcwd(env->gc);
	if (chdir(options[1]) == -1)
	{
		perror("cd");
		env->exit_code = 1;
		return ;
	}
	set_env_var("OLDPWD", oldpwd, env);
	set_env_var("PWD", gc_getcwd(env->gc), env);
	env->exit_code = 0;
}
