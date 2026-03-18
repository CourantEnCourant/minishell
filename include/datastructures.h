/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:58:22 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/03/17 17:47:20 by weizhang         ###   ########.fr       */
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
	void	**arr;
	size_t	len;
	t_gc	*gc;
	void	(*repr)(t_darray *self);
	void	*(*peep)(t_darray *self);
	void	(*insert)(t_darray *self, size_t i, void *item);
	void	(*push)(t_darray *self, void *item);
	void	*(*pop_i)(t_darray *self, size_t i);
	void	*(*pop)(t_darray *self);
};

t_darray	*init_darray(t_gc *gc);

#endif
