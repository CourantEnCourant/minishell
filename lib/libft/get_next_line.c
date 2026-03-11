/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:18:22 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/06 13:39:16 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"

static size_t	ft_strlen_sep(const char *s, char sep)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != sep)
		len++;
	return (len);
}

static int	clean_stash_ptr(char **stash, char **ptr)
{
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (ptr && *ptr)
	{
		free(*ptr);
		ptr = NULL;
	}
	return (0);
}

static int	extend_stash(char **stash, int fd)
{
	char	*temp;
	char	*temp2;
	int		read_result;

	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
		return (clean_stash_ptr(stash, NULL));
	read_result = read(fd, temp, BUFFER_SIZE);
	if (read_result == 0)
		return (clean_stash_ptr(NULL, &temp));
	if (read_result == -1)
	{
		clean_stash_ptr(stash, &temp);
		return (-1);
	}
	temp2 = ft_strjoin(*stash, temp);
	if (!temp2)
	{
		clean_stash_ptr(stash, &temp);
		return (-1);
	}
	clean_stash_ptr(stash, &temp);
	*stash = temp2;
	return (1);
}

static char	*extract_line(char **stash)
{
	int		stash_len;
	char	*temp;
	int		temp_len;
	char	*temp2;

	stash_len = ft_strlen_sep(*stash, '\0');
	if (stash_len == 0)
		return (clean_stash_ptr(stash, NULL), NULL);
	temp_len = ft_strlen_sep(*stash, '\n') + 1;
	temp = ft_substr(*stash, 0, temp_len);
	if (!temp)
		return (clean_stash_ptr(stash, NULL), NULL);
	temp2 = ft_substr(*stash, temp_len, stash_len - temp_len);
	if (!temp2)
		return (clean_stash_ptr(stash, &temp), NULL);
	free(*stash);
	*stash = temp2;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	int			read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_calloc(1, sizeof(char));
	if (!stash[fd])
		return (NULL);
	while (!ft_strchr(stash[fd], '\n'))
	{
		read_result = extend_stash(&stash[fd], fd);
		if (read_result == 0)
			break ;
		if (read_result == -1)
			return (NULL);
	}
	return (extract_line(&stash[fd]));
}
