/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 21:33:33 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/09 21:38:40 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minishell.h"

bool	startswith(void *s, void *ref);

void	unset(char **options, t_env *env)
{
	size_t	i;
	size_t	elem_i;

	i = 0;
	while (options[i])
	{
		elem_i = env->envp->find_i(env->envp, startswith, 
				gc_strjoin(options[i], "=", env->gc));
		if (elem_i != env->envp->len)
			env->envp->pop_i(env->envp, elem_i);
		i++;
	}
	env->exit_code = 0;
}
