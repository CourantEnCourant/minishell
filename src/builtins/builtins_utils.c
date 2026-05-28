/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:59:00 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/26 21:02:09 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **options, t_env *env);
void	echo(char **options, t_env *env);
void	exit_minishell(char **options, int fds[2], t_env *env);
void	export(char **options, t_env *env);
void	pwd(char **options, t_env *env);
void	unset(char **options, t_env *env);
void	print_env(char **options, t_env *env);

void	exec_builtins(char *cmd, char **options, int fds[2], t_env *env)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		pwd(options, env);
	else if (ft_strcmp(cmd, "exit") == 0)
		exit_minishell(options, fds, env);
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
