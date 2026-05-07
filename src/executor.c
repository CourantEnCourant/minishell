/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:34:51 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/30 21:13:23 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"

int			exec_pipe(t_btree *ast, t_env *env);
int			apply_redirs(t_cmd *cmd, t_env *env);
void		execute(t_btree *ast, t_env *env);
void		exec_builtins(char *cmd, char **options, t_env *env);
bool		strs_eq(void *s1, void *s2);

static void	exec_cmd(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	int		saved_stdin;
	int		saved_stdout;

	if (env->builtins->any(env->builtins, strs_eq, cmd->argv[0]))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (apply_redirs(cmd, env) == 0)
			exec_builtins(cmd->argv[0], cmd->argv, env);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		env->exit_code = 1;
		return ;
	}
	if (pid == 0)
	{
		status = apply_redirs(cmd, env);
		if (status == 0)
			status = gc_execvp(cmd->argv[0], cmd->argv, 
						(char **)env->envp->to_arr(env->envp), env->gc);
		env->gc->clean(env->gc);
		exit(status);
	}
	waitpid(pid, &status, 0);
	env->exit_code = status >> 8;
}

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
		execute(ast->left, env);
		status = env->exit_code;
		ast->gc->clean(ast->gc);
		exit(status);
	}
	waitpid(pid, &status, 0);
	env->exit_code = status >> 8;
}

static void	exec_and(t_btree *ast, t_env *env)
{
	execute(ast->left, env);
	if (env->exit_code == 0)
		execute(ast->right, env);
}

void	execute(t_btree *ast, t_env *env)
{
	t_token	*current;

	current = ast->value;
	if (current->type == CMD)
		exec_cmd(current->cmd, env);
	else if (current->type == AND)
		exec_and(ast, env);
	else if (current->type == OR)
	{
		execute(ast->left, env);
		if (env->exit_code != 0)
			execute(ast->right, env);
	}
	else if (current->type == PIPE)
		exec_pipe(ast, env);
	else if (current->type == SUBSHELL)
		exec_subshell(ast, env);
	else
		execute(ast->left, env);
}
