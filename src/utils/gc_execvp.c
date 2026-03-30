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

#include <unistd.h>
#include <stddef.h>
#include "libft.h"
#include "gc_libft.h"

char	**get_paths(t_gc *gc)
{
	size_t		i;
	extern char	**environ;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "PATH", 4) == 0)
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
		execve(cmd, argv, environ);
	paths = get_paths(gc);
	i = 0;
	while (paths[i])
	{
		cmd_abs = gc_strjoin(gc_strjoin(paths[i], "/", gc), cmd, gc);
		if (access(cmd_abs, X_OK) == 0)
			execve(cmd_abs, argv, environ);
		i++;
	}
	return (127);
}
