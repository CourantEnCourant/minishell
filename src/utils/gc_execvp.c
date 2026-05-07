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
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (gc_split(envp[i] + 5, ':', gc));
}

static int	exec_with_path(const char *cmd, char *const argv[])
{
	extern char	**environ;

	execve(cmd, argv, environ);
	perror(cmd);
	if (errno == EACCES)
		return (126);
	return (127);
}

int	gc_execvp(const char *cmd, char *const argv[], char **envp, t_gc *gc)
{
	size_t		i;
	char		*cmd_abs;
	char		**paths;

	if (ft_strchr(cmd, '/'))
		return (exec_with_path(cmd, argv));
	paths = get_paths(envp, gc);
	if (!paths)
		return (127);
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
