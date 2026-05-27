/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdong <fdong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 20:01:30 by fdong             #+#    #+#             */
/*   Updated: 2026/05/27 20:01:30 by fdong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	collect_cmd_heredocs(t_token *token, t_env *env)
{
	t_redir	*redir;
	size_t	i;
	char	*tmp;

	i = -1;
	while (++i < token->cmd->redirs->len)
	{
		redir = token->cmd->redirs->peek_i(token->cmd->redirs, i);
		if (redir->redir_type == HERE_DOC)
		{
			tmp = get_hd_filename(env);
			if (!save_hd_input(redir->filename, tmp, env))
				return (false);
			redir->filename = tmp;
		}
	}
	return (true);
}

bool	collect_heredocs(t_btree *ast, t_env *env)
{
	t_token	*token;

	if (!ast)
		return (true);
	if (!collect_heredocs(ast->left, env) || !collect_heredocs(ast->right, env))
		return (false);
	token = ast->value;
	if (token->type == CMD)
		return (collect_cmd_heredocs(token, env));
	return (true);
}
