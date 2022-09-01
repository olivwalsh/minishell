/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:04:23 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/31 16:05:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	*ft_tabint(const int *t, int c)
{
	int		i;
	int		*tab;

	tab = (int *)t;
	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
			return (tab + i);
		i++;
	}
	return (NULL);
}

int	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

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
