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
#include "libft.h"

bool	str_iseq(char *s1, char *s2)
{
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}
