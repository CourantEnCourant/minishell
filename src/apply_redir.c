/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 20:42:24 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/27 20:01:55 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"

static bool	apply_from_file(t_redir *redir, t_env *env)
{
	int		fd;
	bool	flag;

	flag = true;
	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
	{
		perror(redir->filename);
		env->exit_code = 1;
		return (false);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		env->exit_code = 1;
		flag = false;
	}
	close(fd);
	return (flag);
}

static bool	apply_append_file(t_redir *redir, t_env *env)
{
	int		fd;
	bool	flag;

	flag = true;
	fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		env->exit_code = 1;
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		env->exit_code = 1;
		flag = false;
	}
	close(fd);
	return (flag);
}

static bool	apply_to_file(t_redir *redir, t_env *env)
{
	int		fd;
	bool	flag;

	flag = true;
	fd = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror(redir->filename);
		env->exit_code = 1;
		return (false);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		env->exit_code = 1;
		flag = false;
	}
	close(fd);
	return (flag);
}

static bool	apply_heredoc(t_redir *redir, t_env *env)
{
	int		fd;

	fd = open(redir->filename, O_RDONLY);
	if (fd == -1)
		return (perror("heredoc read open"), env->exit_code = 1, false);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		env->exit_code = 1;
		close(fd);
		return (false);
	}
	close(fd);
	unlink(redir->filename);
	return (true);
}

bool	apply_redirs(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	bool	flag;
	size_t	i;

	flag = true;
	i = 0;
	while (i < cmd->redirs->len)
	{
		redir = cmd->redirs->peek_i(cmd->redirs, i);
		if (redir->redir_type == TO_FILE)
			flag = apply_to_file(redir, env);
		else if (redir->redir_type == APPEND_FILE)
			flag = apply_append_file(redir, env);
		else if (redir->redir_type == FROM_FILE)
			flag = apply_from_file(redir, env);
		else if (redir->redir_type == HERE_DOC)
			flag = apply_heredoc(redir, env);
		if (!flag)
			break ;
		i++;
	}
	return (flag);
}
