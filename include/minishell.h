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

typedef struct s_token t_token;
typedef struct s_lexer t_lexer;

struct s_token
{
	char	*expr;
};

struct s_lexer
{
};

t_lexer	*init_lexer(t_gc *gc);

#endif
