/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 17:11:12 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/18 17:12:57 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include "datastructures.h"
#include "libft.h"
#include "minishell.h"

size_t	len(void **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	repr_strs(char **strs)
{
	size_t	i;

	ft_printf("\"");
	i = 0;
	while (i < len((void **)strs) - 1)
	{
		ft_printf("%s ", strs[i]);
		i++;
	}
	ft_printf("%s\"", strs[i]);
}

void	repr_token(void *ptr)
{
	t_token	*token;

	if (!ptr)
		return ;
	token = ptr;
	token->repr(token);
}

void	repr_node(void *ptr)
{
	t_btree	*node;

	node = ptr;
	repr_token(node->value);
}
