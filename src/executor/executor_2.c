/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:30:17 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/26 20:33:52 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

void	exec_subshell(t_btree *ast, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		env->exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		setup_signals_fork();
		execute(ast->left, env);
		status = env->exit_code;
		ast->gc->clean(ast->gc);
		exit(status);
	}
	waitpid(pid, &status, 0);
	update_exit_code(status, env);
}
