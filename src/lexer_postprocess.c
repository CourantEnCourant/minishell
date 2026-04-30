/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_postprocess.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:50:58 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/02 18:51:02 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "datastructures.h"
#include "minishell.h"

static t_token	*validate_redir(t_darray *ops, size_t i, t_env *env)
{
	t_token	*next;

	if (i + 1 >= ops->len)
	{
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token 'newline'\n");
		env->exit_code = 2;
		return (NULL);
	}
	next = ops->peek_i(ops, i + 1);
	if (next->type != OPERAND)
	{
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token `%s'\n", next->value);
		env->exit_code = 2;
		return (NULL);
	}
	return (next);
}

static size_t	add_to_cmd(t_cmd *cmd, t_darray *ops, size_t i, t_env *env)
{
	t_token	*cur;
	t_token	*next;

	cur = ops->peek_i(ops, i);
	next = validate_redir(ops, i, env);
	if (!next)
		return (0);
	if (ft_strcmp(cur->value, ">") == 0)
		cmd->push_redir(cmd,
			init_redir(TO_FILE, next->value, cmd->gc));
	else if (ft_strcmp(cur->value, ">>") == 0)
		cmd->push_redir(cmd,
			init_redir(APPEND_FILE, next->value, cmd->gc));
	else if (ft_strcmp(cur->value, "<") == 0)
		cmd->push_redir(cmd,
			init_redir(FROM_FILE, next->value, cmd->gc));
	return (i + 2);
}

static size_t	collect_argv(t_darray *operands, size_t i, t_darray *cmds, t_env *env)
{
	t_darray	*argv;
	t_token		*current;
	t_cmd		*cmd;

	argv = init_darray(cmds->gc);
	cmd = init_cmd(operands->gc);
	while (i < operands->len)
	{
		current = operands->peek_i(operands, i);
		if (current->type == OPERAND && ++i)
			argv->push(argv, current->value);
		else if (current->type == REDIR)
		{
			i = add_to_cmd(cmd, operands, i, env);
			if (i == 0)
				return (0);
		}
		else
			break ;
	}
	cmd->set_argv(cmd, (char **)argv->to_arr(argv));
	cmds->push(cmds, init_cmd_token(cmd, cmds->gc));
	return (i);
}

t_darray	*postprocess(t_darray *operands, t_env *env)
{
	t_darray	*cmds;
	t_token		*current;
	size_t		i;

	cmds = init_darray(operands->gc);
	i = 0;
	while (i < operands->len)
	{
		current = operands->peek_i(operands, i);
		if (current->type & (OPERAND | REDIR))
		{
			i = collect_argv(operands, i, cmds, env);
			if (i == 0)
				return (NULL);
		}
		else
		{
			cmds->push(cmds, current);
			i++;
		}
	}
	return (cmds);
}
