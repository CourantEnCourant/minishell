/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:00:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/09 20:07:37 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include "libft.h"
#include "minishell.h"

size_t	len(void **arr);
bool	str_is_num(char *s);
bool	int64_overflow(char *n);

static bool	check_args(char **args, t_env *env)
{
	if (len((void **)args) == 1)
		return (true);
	if (!str_is_num(args[1]) || int64_overflow(args[1]))
	{
		ft_dprintf(STDERR_FILENO,
			"exit: %s: numeric argument required\n", args[1]);
		env->exit_code = 2;
		return (true);
	}
	if (len((void **)args) > 2)
	{
		ft_dprintf(STDERR_FILENO, "exit: too many arguments\n");
		env->exit_code = 1;
		return (false);
	}
	env->exit_code = ft_atoi(args[1]);
	return (true);
}

void	exit_minishell(char **options, int fds[2], t_env *env)
{
	int	exit_code;

	printf("exit\n");
	if (!check_args(options, env))
		return ;
	exit_code = env->exit_code;
	if (fds)
	{
		close(fds[0]);
		close(fds[1]);
	}
	rl_clear_history();
	env->gc->clean(env->gc);
	exit(exit_code);
}
