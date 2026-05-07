/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 21:39:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/16 21:41:49 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "datastructures.h"
#include "minishell.h"

int		apply_redirs(t_cmd *cmd, t_env *env);
void	exec_subshell(t_btree *ast, t_env *env);

static void	flatten_recur(t_btree *ast, t_darray *nodes)
{
	t_token		*current;

	current = ast->value;
	if (current->type == CMD || current->type == SUBSHELL)
		nodes->push(nodes, ast);
	if (current->type == PIPE)
	{
		flatten_recur(ast->left, nodes);
		flatten_recur(ast->right, nodes);
	}
}

t_darray	*flatten(t_btree *ast)
{
	t_darray	*nodes;

	nodes = init_darray(ast->gc);
	flatten_recur(ast, nodes);
	return (nodes);
}

static void	manage_dup(int in_fd, int out_fd, t_gc *gc)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(in_fd);
			gc->clean(gc);
			exit(1);
		}
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(out_fd);
			gc->clean(gc);
			exit(1);
		}
		close(out_fd);
	}
}

void	exec_child(t_btree *node, int in_fd, int out_fd, t_env *env, t_gc *gc)
{
	t_token	*token;
	t_cmd	*cmd;
	int		exit_code;

	manage_dup(in_fd, out_fd, gc);
	token = node->value;
	if (token->type == CMD)
	{
		cmd = token->cmd;
		exit_code = apply_redirs(cmd, env);
		if (exit_code == 0)
			exit_code = gc_execvp(cmd->argv[0], cmd->argv, 
					(char **)env->envp->to_arr(env->envp), gc);
		gc->clean(gc);
		exit(exit_code);
	}
	exec_subshell(node, env);
	exit_code = env->exit_code;
	gc->clean(gc);
	exit(exit_code);
}
