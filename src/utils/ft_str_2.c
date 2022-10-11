/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:13:55 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 16:28:33 by owalsh           ###   ########.fr       */
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

char	*ft_strchr(char *str, int c)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] == to_find[i])
	{
		i++;
		if (to_find[i] == '\0')
			return (str + i);
	}
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
