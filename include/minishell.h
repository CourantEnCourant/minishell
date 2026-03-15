/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 21:07:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/14 21:07:50 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "gc_libft.h"
# include "datastructures.h"

typedef struct s_token t_token;
typedef struct s_parser t_parser;

struct s_token
{
	char	*expr;
};

struct s_parser
{
	t_darray	*(*tokenize)(char *cmd, t_gc *gc);
};

t_parser	*init_parser(t_gc *gc);

#endif
