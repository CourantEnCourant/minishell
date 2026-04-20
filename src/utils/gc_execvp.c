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

static char	**get_paths(t_gc *gc)
{
	size_t		i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!environ[i])
		return (NULL);
	return (gc_split(environ[i] + 5, ':', gc));
}

int	gc_execvp(const char *cmd, char *const argv[], t_gc *gc)
{
	size_t		i;
	char		*cmd_abs;
	char		**paths;
	extern char	**environ;

	if (ft_strchr(cmd, '/'))
	{
		execve(cmd, argv, environ);
		perror(cmd);
		if (errno == EACCES)
			return (126);
		return (127);
	}
	paths = get_paths(gc);
	if (!paths)
		return (127);
	i = 0;
	while (paths[i])
	{
		cmd_abs = gc_strjoin(gc_strjoin(paths[i], "/", gc), cmd, gc);
		if (access(cmd_abs, X_OK) == 0)
			execve(cmd_abs, argv, environ);
		i++;
	}
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", cmd);
	return (127);
}
