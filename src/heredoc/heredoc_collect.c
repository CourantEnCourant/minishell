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

char	*expand_arg(char *arg, t_env *env);
void	*strip_sentinel(void *s, t_gc *gc);

static bool	is_hd_quoted(char *s)
{
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			return (true);
		s++;
	}
	return (false);
}

static bool	collect_cmd_heredocs(t_token *token, t_env *env)
{
	t_redir	*redir;
	size_t	i;
	char	*tmp;
	bool	quoted;

	i = -1;
	while (++i < token->cmd->redirs->len)
	{
		redir = token->cmd->redirs->peek_i(token->cmd->redirs, i);
		if (redir->redir_type == HERE_DOC)
		{
			quoted = is_hd_quoted(redir->filename);
			redir->filename = strip_sentinel(
					expand_arg(redir->filename, env), env->gc);
			tmp = get_hd_filename(env);
			if (!save_hd_input(redir->filename, tmp, quoted, env))
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
