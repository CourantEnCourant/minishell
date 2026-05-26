/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 21:59:03 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/12 01:40:36 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include "datastructures.h"
#include "libft.h"
#include "minishell.h"

bool	key_match(void *envar, void *str);
size_t	len(void **arr);
bool	envar_gt(void *e1, void *e2);
char	*extract_key(char *envar, t_gc *gc);
char	*extract_value(char *envar, t_gc *gc);

static void	print_export(t_env *env)
{
	t_darray	*envp_copy;
	t_envar		*envar;
	size_t		i;

	envp_copy = env->envp->copy(env->envp);
	envp_copy->sort(envp_copy, envar_gt);
	i = 0;
	while (i < envp_copy->len)
	{
		envar = envp_copy->peek_i(envp_copy, i);
		if (envar->exported)
		{
			printf("export %s", envar->key);
			if (envar->value)
				printf("=\"%s\"", envar->value);
			printf("\n");
		}
		i++;
	}
}

static void	add_to_env(char *arg, t_env *env)
{
	char	*key;
	char	*value;
	size_t	target_i;
	t_envar	*envar;

	key = extract_key(arg, env->gc);
	value = extract_value(arg, env->gc);
	target_i = env->envp->find_i(env->envp, key_match, key);
	if (target_i != env->envp->len)
	{
		envar = env->envp->peek_i(env->envp, target_i);
		envar->exported = true;
		if (value)
			envar->value = value;
	}
	else
		env->envp->push(env->envp, init_envar_from_str(arg, env->gc));
}

static bool	is_valid_arg(char *arg, t_gc *gc)
{
	char	*key;
	size_t	i;

	key = extract_key(arg, gc);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (false);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	export(char **options, t_env *env)
{
	size_t			i;
	unsigned char	flag;

	flag = 0;
	if (len((void **)options) == 1)
		print_export(env);
	i = 1;
	while (options[i])
	{
		if (is_valid_arg(options[i], env->gc))
			add_to_env(options[i], env);
		else
		{
			ft_dprintf(STDERR_FILENO,
				"export: '%s': not a valid identifier\n", options[i]);
			flag = 1;
		}
		i++;
	}
	env->exit_code = flag;
}
