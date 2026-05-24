/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:10:52 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/27 16:25:10 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include "libft.h"
#include "gc_libft.h"
#include "minishell.h"

static char	**get_paths(char **envp, t_gc *gc)
{
	size_t		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (gc_split(envp[i] + 5, ':', gc));
		i++;
	}
	return (NULL);
}

static int	manual_exec(const char *cmd, char *const argv[], char **envp)
{
	execve(cmd, argv, envp);
	perror(cmd);
	if (errno == EACCES)
		return (126);
	return (127);
}

int	gc_execvp(const char *cmd, char *const argv[], char **envp, t_gc *gc)
{
	size_t	i;
	char	*cmd_abs;
	char	**paths;

	paths = get_paths(envp, gc);
	if (ft_strchr(cmd, '/') || !paths)
		return (manual_exec(cmd, argv, envp));
	i = -1;
	while (paths[++i])
	{
		cmd_abs = gc_strjoin(gc_strjoin(paths[i], "/", gc), cmd, gc);
		if (access(cmd_abs, X_OK) == 0)
			execve(cmd_abs, argv, envp);
	}
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", cmd);
	return (127);
}
