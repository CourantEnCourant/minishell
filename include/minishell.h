/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:07:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/26 15:21:30 by anying           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gc_libft.h"
# include "datastructures.h"

typedef struct s_parser	t_parser;

typedef enum e_lexer_state
{
	TEXT,
	SINGLE,
	DOUBLE,
}	t_lexer_state;

struct s_parser
{
	bool			(*is_valid_cmd)(char *cmd);
	t_darray		*(*tokenize)(char *cmd, t_gc *gc);
};

t_parser	*init_parser(t_gc *gc);

char		*gc_readline(const char *prompt, t_gc *gc);
char		*gc_getcwd(t_gc *gc);

#endif
