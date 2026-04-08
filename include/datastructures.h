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

# ifndef DARRAY_LEN
#  define DARRAY_LEN 42
# endif

# include <stddef.h>
# include <stdbool.h>
# include "gc_libft.h"

typedef struct s_darray	t_darray;
struct s_darray
{
	void	**arr;
	size_t	len;
	size_t	capacity;
	t_gc	*gc;
	void	(*repr)(t_darray *self, void (*repr_item)(void *value));
	void	*(*peek_i)(t_darray *self, size_t i);
	void	*(*peek)(t_darray *self);
	void	(*insert)(t_darray *self, size_t i, void *item);
	void	(*push)(t_darray *self, void *item);
	void	*(*pop_i)(t_darray *self, size_t i);
	void	*(*pop)(t_darray *self);
	void	*(*reduce)(t_darray *s,
			void *(*f)(void *i1, void *i2, t_gc *gc), void *a);
};
t_darray	*init_darray(t_gc *gc);

typedef struct s_btree	t_btree;
struct s_btree
{
	void	*value;
	t_btree	*left;
	t_btree	*right;
	t_gc	*gc;
	void	(*repr)(t_btree *s, void (*repr_v)(void *v));
};
t_btree		*init_btree(void *value, t_gc *gc);

#endif
