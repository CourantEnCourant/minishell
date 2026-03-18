/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 13:54:54 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/11 13:55:27 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <assert.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "minishell.h"

static void	test_parser_tokenize(t_gc *gc)
{
	t_parser	*parser;
	t_darray	*cmds;
	char		*s;

	printf("==========TEST_PARSER_TOKENIZE==========\n");
	parser = init_parser(gc);

	// empty string
	s = "";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	// single pipe
	s = "ls -l | grep -la";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	// pipe without spaces
	s = "ls -l|grep -la";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	// pipe + and
	s = "ls -l | grep -la && cat -e";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	// and without spaces
	s = "ls -l | grep -la&&cat -e";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	// simple command, no operators
	s = "echo hello world";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	// multiple pipes
	s = "cat file | grep foo | wc -l";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	// operators inside single quotes (should not tokenize)
	s = "echo '|| && |' | cat";
	printf("Tokenizing %s\n", s);
	cmds = parser->tokenize(s, gc);
	cmds->repr(cmds);
	printf("\n");

	printf("==========ALL TESTS PASSED==========\n\n");
}

static void test_parser_is_valid_cmd(t_gc *gc)
{
	t_parser	*parser;
	char		*s;

	printf("==========TEST_PARSER_IS_VALID_CMD==========\n");
	parser = init_parser(gc);

	// basic
	s = "";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "echo hello";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);

	// single quotes
	s = "'hello'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "''";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "'hello";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);

	// double quotes
	s = "\"hello\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "\"\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "\"hello";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);

	// mixed quotes
	s = "\"'\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "'\"'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "\"''\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "'\"\"'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "\"'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "'\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "\"'\"''";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "'\"'\"'\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);

	// parentheses
	s = "()";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "(())";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "()()";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "((()))";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "(";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = ")";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "((";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "))";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = ")(";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "(()";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "())";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);

	// parentheses inside quotes (should be ignored)
	s = "'()'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "'('";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "')'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "\"()\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "\"(\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "\")\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);

	// quotes inside parentheses
	s = "('hello')";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "(\"hello\")";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);

	// combined edge cases
	s = "''()()";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "(\")\"";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "(')'";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "\"(\")";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "'(')";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);

	// realistic commands
	s = "(echo hello && echo world)";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "(echo hello && (echo world))";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == true);
	s = "echo 'unclosed";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);
	s = "echo \"unclosed";
	printf("Testing %s\n", s);
	assert(parser->is_valid_cmd(s) == false);

	printf("==========ALL TESTS PASSED==========\n\n");
}

int main(void)
{
	t_gc	*gc;

	gc = init_gc();
	test_parser_is_valid_cmd(gc);
	test_parser_tokenize(gc);
	gc->clean(gc);
}
*/
