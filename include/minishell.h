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

typedef enum e_lexer_state
{
	TEXT,
	SINGLE,
	DOUBLE,
}	t_lexer_state;

typedef enum e_redir_type
{
	TO_FILE,
	APPEND_FILE,
	FROM_FILE,
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	redir_type;
	char			*filename;
	t_gc			*gc;
}	t_redir;
t_redir		*init_redir(t_redir_type type, char *filename, t_gc *gc);

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char		**argv;
	t_darray	*redirs;
	t_gc		*gc;
	void		(*set_argv)(t_cmd *self, char **argv);
	void		(*push_redir)(t_cmd *self, t_redir *redir);
};
t_cmd		*init_cmd(t_gc *gc);

typedef enum e_token_type
{
	AND,
	OR,
	PIPE,
	SUBSHELL,
	CLOSE_PAREN,
	OPERAND,
	REDIR,
	CMD,
}	t_token_type;

typedef struct s_token	t_token;
struct s_token
{
	union
	{
		char	*value;
		t_cmd	*cmd;
	};
	t_token_type	type;
	int				bind_left;
	int				bind_right;
	void			(*repr)(t_token *cmd);
};
t_token		*init_token(char *value, t_gc *gc);
t_token		*init_cmd_token(t_cmd *cmd, t_gc *gc);

char		*gc_readline(const char *prompt, t_gc *gc);
char		*gc_getcwd(t_gc *gc);
t_btree		*parse(char *input, t_gc *gc);
int			execute(t_btree *ast);

#endif
