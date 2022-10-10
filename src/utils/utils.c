/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:04:23 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 15:06:58 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_result(char *res)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(res) + 1));
	if (!new)
		return (err_msg_str(MALLOC_ERR));
	ft_strncpy(new, res, ft_strlen(res));
	return (new);
}

char	*get_newname(char *name)
{
	char	*new_name;

	if (!name)
		return (NULL);
	new_name = NULL;
	new_name = ft_strjoin(new_name, name, 1);
	new_name = ft_strjoin(new_name, "=", 1);
	return (new_name);
}

char	*ft_getenv(char *name)
{
	char	**env;
	char	*res;
	char	*new_name;
	int		i;

	new_name = get_newname(name);
	if (!new_name)
		return (NULL);
	env = g_global.data->shell.env;
	i = -1;
	while (env && env[++i])
	{
		res = ft_strstr(env[i], new_name);
		if (res && !ft_strncmp(env[i], new_name, ft_strlen(new_name)))
		{
			res = create_result(res);
			break ;
		}
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

int	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}
