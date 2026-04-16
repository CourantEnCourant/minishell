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
#include "libft.h"
#include "datastructures.h"
#include "minishell.h"

static size_t	collect_argv(t_darray *operands, size_t i, t_darray *cmds)
{
	t_darray	*argv;
	t_token		*current;
	t_token		*next;
	t_cmd		*cmd;

	argv = init_darray(cmds->gc);
	cmd = init_cmd(operands->gc);
	while (i < operands->len)
	{
		current = operands->peek_i(operands, i);
		if (current->type == OPERAND)
		{
			argv->push(argv, current->value);
			i++;
		}
		else if (current->type == REDIR)
		{
			if (i + 1 >= operands->len)
				return (0);
			next = operands->peek_i(operands, i + 1);
			if (next->type != OPERAND)
				return (0);
			if (ft_strcmp(current->value, ">") == 0)
			{
				cmd->push_redir(cmd,
					init_redir(TO_FILE, next->value, operands->gc));
				i += 2;
			}
			else if (ft_strcmp(current->value, ">>") == 0)
			{
				cmd->push_redir(cmd,
					init_redir(APPEND_FILE, next->value, operands->gc));
				i += 2;
			}
			else if (ft_strcmp(current->value, "<") == 0)
			{
				cmd->push_redir(cmd,
					init_redir(FROM_FILE, next->value, operands->gc));
				i += 2;
			}
		}
		else
			break ;
	}
	cmd->set_argv(cmd, (char **)argv->to_arr(argv));
	cmds->push(cmds, init_cmd_token(cmd, cmds->gc));
	return (i);
}

t_darray	*postprocess(t_darray *operands)
{
	t_darray	*cmds;
	t_token		*current;
	size_t		i;

	cmds = init_darray(operands->gc);
	i = 0;
	while (i < operands->len)
	{
		current = operands->peek_i(operands, i);
		if (current->type == OPERAND || current->type == REDIR)
		{
			i = collect_argv(operands, i, cmds);
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
