/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:07:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/29 00:00:55 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "gc_libft.h"
# include "datastructures.h"

typedef struct s_parser	t_parser;
typedef struct s_token	t_token;
typedef struct s_exec	t_exec;
typedef struct s_pipe	t_pipe;

typedef enum e_lexer_state
{
	TEXT,
	SINGLE,
	DOUBLE,
}	t_lexer_state;

typedef enum e_token_type
{
	AND,
	OR,
	PIPE,
	SUBSHELL,
	CLOSE_PAREN,
	OPERAND,
}	t_token_type;

struct s_token
{
	char			*value;
	t_token_type	type;
	int				bind_left;
	int				bind_right;
	void			(*repr)(t_token *cmd);
};
t_token		*init_token(char *value, t_gc *gc);

struct s_parser
{
	bool			(*is_valid_cmd)(char *cmd);
	t_darray		*(*tokenize)(char *cmd, t_gc *gc);
	t_btree			*(*parse)(t_darray *tokens);
	bool			(*is_valid_tree)(t_btree * ast);
};
t_parser	*init_parser(t_gc *gc);

struct s_exec
{
	t_gc	*gc;
	int		(*execute)(t_btree *ast);
};
t_exec		*init_exec(t_gc *gc);

char		*gc_readline(const char *prompt, t_gc *gc);
char		*gc_getcwd(t_gc *gc);

#endif
