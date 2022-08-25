/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:04:23 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/25 15:04:34 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	if (!src || !dst)
		return (NULL);
	while (i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
