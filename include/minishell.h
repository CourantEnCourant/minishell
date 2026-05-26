/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:19:44 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/11 00:19:46 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include "gc_libft.h"
# include "datastructures.h"

extern int				g_signal;

typedef enum e_dfa_state
{
	TEXT,
	SINGLE,
	DOUBLE,
	DOLLAR,
	ALPHA,
}	t_dfa_state;

typedef struct s_exp
{
	t_dfa_state	state;
	t_dfa_state	previous;
	t_darray	*fragments;
	size_t		i;
	size_t		start;
}	t_exp;

typedef enum e_redir_type
{
	TO_FILE,
	APPEND_FILE,
	FROM_FILE,
}	t_redir_type;

typedef struct s_redir	t_redir;
struct s_redir
{
	t_redir_type	redir_type;
	char			*filename;
	t_gc			*gc;
	void			(*set_filename)(t_redir *self, char *filename);
};
t_redir		*init_redir(t_redir_type type, char *filename, t_gc *gc);

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	t_darray	*argv;
	t_darray	*redirs;
	t_gc		*gc;
	void		(*set_argv)(t_cmd *self, t_darray *argv);
	void		(*push_redir)(t_cmd *self, t_redir *redir);
};
t_cmd		*init_cmd(t_gc *gc);

typedef enum e_token_type
{
	AND = 1,
	OR = 1 << 1,
	PIPE = 1 << 2,
	SUBSHELL = 1 << 3,
	CLOSE_PAREN = 1 << 4,
	OPERAND = 1 << 5,
	REDIR = 1 << 6,
	CMD = 1 << 7,
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

typedef struct s_envar	t_envar;
struct s_envar
{
	char	*key;
	char	*value;
	bool	exported;
	t_gc	*gc;
	char	*(*to_str)(t_envar *self);
};
t_envar		*init_envar(char *key, char *value, bool exported, t_gc *gc);
t_envar		*init_envar_from_str(char *envar_str, t_gc *gc);

typedef struct s_env	t_env;
struct s_env
{
	unsigned char	exit_code;
	t_darray		*builtins;
	t_darray		*envp;
	t_gc			*gc;
	char			**(*export_envp)(t_env *self);
	void			(*set_envar)(t_env *self, char *key, char *value);
};
t_env		*init_env(t_gc *gc);

int			gc_execvp(const char *cmd, char *const argv[],
				char **envp, t_gc *gc);
char		*gc_readline(const char *prompt, t_gc *gc);
char		*gc_getcwd(t_gc *gc);
t_btree		*parse(char *input, t_env *env);
void		expand_cmd(t_cmd *cmd, t_env *env);
void		execute(t_btree *ast, t_env *env);
void		setup_signals_interactive(void);
void		setup_signals_execution(void);
void		setup_signals_fork(void);
void		update_exit_code(int code, t_env *env);

#endif
