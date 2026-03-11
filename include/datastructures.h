/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:58:22 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/02/04 11:58:41 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTURES_H
# define DATASTRUCTURES_H

# ifndef LIST_LEN
#  define LIST_LEN 42
# endif

# include <stddef.h>
# include <stdbool.h>
# include "gc_libft.h"

typedef struct s_darray	t_darray;
struct s_darray
{
	int		*arr;
	size_t	len;
	void	(*repr)(t_darray *self);
	int		(*peep)(t_darray *self);
	void	(*insert)(t_darray *self, size_t i, int num, t_gc *gc);
	void	(*push)(t_darray *self, int num, t_gc *gc);
	int		(*pop_i)(t_darray *self, size_t i);
	int		(*pop)(t_darray *self);
	bool	(*is_sorted)(t_darray * self);
};

t_darray	*init_darray(t_gc *gc);

#endif
