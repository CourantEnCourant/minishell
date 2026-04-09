/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 20:40:48 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/17 17:46:45 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

bool			quotes_paren_match(char *cmd);
t_darray		*tokenize(char *cmd, t_gc *gc);

static bool	is_valid_tree(t_btree *ast)
{
	t_token	*current;

	if (!ast || !ast->value)
		return (false);
	current = ast->value;
	if (current->type == OPERAND)
		return (!ast->left && !ast->right);
	else if (current->type == SUBSHELL)
		return (is_valid_tree(ast->left) && !ast->right);
	else if (current->type == CLOSE_PAREN)
		return (false);
	else
		return (is_valid_tree(ast->left) && is_valid_tree(ast->right));
}

static t_btree	*parse_recur(t_darray *tokens, size_t *i, int min_bp);

static t_btree	*join_op(t_btree *left, t_darray *tokens, size_t *i)
{
	t_token	*op;
	t_btree	*node;

	op = tokens->peek_i(tokens, *i);
	(*i)++;
	node = init_btree(op, tokens->gc);
	node->left = left;
	node->right = parse_recur(tokens, i, op->bind_right);
	return (node);
}

static t_btree	*parse_recur(t_darray *tokens, size_t *i, int min_bp)
{
	t_token	*token;
	t_btree	*node;

	if (*i >= tokens->len)
		return (NULL);
	token = tokens->peek_i(tokens, *i);
	if (token->type == SUBSHELL)
	{
		node = init_btree(token, tokens->gc);
		(*i)++;
		node->left = parse_recur(tokens, i, 0);
	}
	else
		node = init_btree(token, tokens->gc);
	(*i)++;
	while (*i < tokens->len)
	{
		token = tokens->peek_i(tokens, *i);
		if (token->type == CLOSE_PAREN || token->bind_left < min_bp)
			break ;
		node = join_op(node, tokens, i);
	}
	return (node);
}

static t_btree	*parse(t_darray *tokens)
{
	size_t	i;

	i = 0;
	return (parse_recur(tokens, &i, 0));
}

t_parser	*init_parser(t_gc *gc)
{
	t_parser	*parser;

	parser = gc_malloc(sizeof(t_parser), gc);
	parser->is_valid_cmd = quotes_paren_match;
	parser->tokenize = tokenize;
	parser->parse = parse;
	parser->is_valid_tree = is_valid_tree;
	return (parser);
}
