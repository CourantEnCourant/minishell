/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 17:20:00 by fdong             #+#    #+#             */
/*   Updated: 2026/05/13 15:37:34 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

void	update_exit_code(int status, t_env *env)
{
	if (WIFEXITED(status))
		env->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		env->exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGINT)
			ft_dprintf(STDERR_FILENO, "\n");
		else if (WTERMSIG(status) == SIGQUIT)
			ft_dprintf(STDERR_FILENO, "Quit (core dumped)\n");
		else if (WTERMSIG(status) == SIGSEGV)
			ft_dprintf(STDERR_FILENO, "Segmentation fault: %d\n",
				WTERMSIG(status));
	}
}
