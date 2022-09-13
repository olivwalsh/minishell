/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:04:23 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 15:24:51 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*create_result(char *res)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(res) + 1));
	if (!new)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	ft_strncpy(new, res, ft_strlen(res));
	return (new);
}

char	*ft_getenv(char *name)
{
	char	**env;
	char	*res;
	char	*new_name;
	int		i;

	if (!name)
		return (NULL);
	new_name = NULL;
	new_name = ft_strjoin(new_name, name, 1);
	new_name = ft_strjoin(new_name, "=", 1);
	if (!new_name)
		return (NULL);
	env = g_global.data->shell.env;
	i = 0;
	while (env && env[i])
	{
		res = ft_strstr(env[i], new_name);
		if (res && !ft_strncmp(env[i], new_name, ft_strlen(new_name)))
		{
			res = create_result(res);
			break ;
		}
		else
			i++;
	}
	free(new_name);
	return (res);
}

int	ft_tablen(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

int	*ft_tabint(int *table, int c)
{
	int		i;

	i = 0;
	while (table && table[i] != 0 && table[i] != -2)
	{
		if (table[i] == c)
			return (table + i);
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
