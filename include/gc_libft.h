/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_libft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:31:24 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/06 00:00:00 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_LIBFT_H
# define GC_LIBFT_H

# include <stddef.h>
# include "libft.h"

typedef struct s_gc	t_gc;
struct s_gc
{
	t_list	*start;
	void	(*clean)(t_gc *self);
	void	(*add)(t_gc *self, void *item);
};

t_gc	*init_gc(void);
void	*gc_malloc(size_t size, t_gc *gc);
void	*gc_calloc(size_t nmemb, size_t size, t_gc *gc);
void	*gc_strdup(char *s, t_gc *gc);
char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc *gc);
char	*gc_strjoin(char const *s1, char const *s2, t_gc *gc);
char	*gc_get_next_line(int fd, t_gc *gc);
char	**gc_split(char const *s, char c, t_gc *gc);

#endif
