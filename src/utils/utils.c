/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:04:23 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 18:50:04 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_result(char *res)
{
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(res) + 1));
	if (!new)
		return (err_msg_str(-2, 0));
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

int	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}
