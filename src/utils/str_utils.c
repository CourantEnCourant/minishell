/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 23:55:28 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/01 23:56:37 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

bool	strs_eq(void *s1, void *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}

bool	startswith(void *s, void *ref)
{
	return (ft_strncmp(s, ref, ft_strlen(ref)) == 0);
}
