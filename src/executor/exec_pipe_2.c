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

bool	apply_redirs(t_cmd *cmd, t_env *env);
void	exec_subshell(t_btree *ast, t_env *env);
void	exec_builtins(char *cmd, char **options, int fds[2], t_env *env);
bool	strs_eq(void *s1, void *s2);

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

static void	exec_cmd_child(t_btree *node, t_env *env)
{
	t_token	*token;
	t_cmd	*cmd;
	char	**argv;

	token = node->value;
	cmd = token->cmd;
	expand_cmd(cmd, env);
	argv = (char **)cmd->argv->to_arr(cmd->argv);
	if (!apply_redirs(cmd, env))
		return ;
	if (cmd->argv->len == 0)
		env->exit_code = 0;
	else if (env->builtins->any(env->builtins, strs_eq, argv[0]))
		exec_builtins(argv[0], argv, NULL, env);
	else
		env->exit_code = gc_execvp(argv[0], argv,
				(char **)env->export_envp(env), env->gc);
}

void	exec_child(t_btree *node, int in_fd, int out_fd, t_env *env)
{
	t_token	*token;
	int		exit_code;

	manage_dup(in_fd, out_fd, env->gc);
	setup_signals_fork();
	token = node->value;
	if (token->type == SUBSHELL)
		exec_subshell(node, env);
	else
		exec_cmd_child(node, env);
	exit_code = env->exit_code;
	env->gc->clean(env->gc);
	exit(exit_code);
}
