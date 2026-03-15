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

# ifndef DARRAY_LEN
#  define DARRAY_LEN 42
# endif

# include <stddef.h>
# include <stdbool.h>
# include "gc_libft.h"

typedef struct s_darray	t_darray;
typedef struct s_btree	t_btree;

struct s_darray
{
	void	**arr;
	size_t	len;
	size_t	capacity;
	void	(*repr)(t_darray *self);
	void	*(*peep)(t_darray *self);
	void	(*insert)(t_darray *self, size_t i, void *item, t_gc *gc);
	void	(*push)(t_darray *self, void *item, t_gc *gc);
	void	*(*pop_i)(t_darray *self, size_t i);
	void	*(*pop)(t_darray *self);
};
t_darray	*init_darray(t_gc *gc);

struct s_btree
{
	void	*value;
	t_btree	*left;
	t_btree	*right;
};
t_btree		*init_btree(t_gc *gc);

#endif
