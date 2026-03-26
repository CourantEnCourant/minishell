/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:35:54 by anying            #+#    #+#             */
/*   Updated: 2026/03/27 10:58:22 by anying           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

char	*gc_getcwd(t_gc *gc)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, cwd);
	return (cwd);
}
