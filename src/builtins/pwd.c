/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 21:10:30 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/30 21:12:24 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

void pwd(char **options, t_env *env)
{
	(void)(options);
	printf("%s\n", gc_getcwd(env->gc));
	env->exit_code = 0;
}
