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
	gc->clean(gc);
}
*/
