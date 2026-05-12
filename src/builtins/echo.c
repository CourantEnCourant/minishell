/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 21:03:28 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/11 21:29:45 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include "minishell.h"

size_t	len(void **arr);

void	echo(char **options, t_env *env)
{
	bool	n;
	size_t	i;

	n = false;
	i = 1;
	while (options[i])
	{
		if (ft_strcmp(options[i], "-n") == 0)
		{
			n = true;
			i++;
			continue ;
		}
		break ;
	}
	while (options[i])
	{
		printf("%s", options[i]);
		if (options[i + 1])
			printf(" ");
		i++;
	}
	if (n == false)
		printf("\n");
	env->exit_code = 0;
}
