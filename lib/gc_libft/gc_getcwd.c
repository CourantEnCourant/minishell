/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:35:54 by anying            #+#    #+#             */
/*   Updated: 2026/03/25 18:14:58 by anying           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gc_libft.h"

char	*gc_getcwd(t_gc *gc)
{
	char	*cwd;
	cwd = get(NULL, 0);
	if (!cwd)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, cwd);
	return (cwd);
}