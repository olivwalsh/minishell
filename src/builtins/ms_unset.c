/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:23 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/13 15:42:01 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_new(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
	err_msg(-2, 0);
	return (NULL);
}

char	**malloc_unset(char **old, char **new, int i, int *j)
{
	new[*j] = malloc(sizeof(char) * (ft_strlen(old[i]) + 1));
	if (!new[*j])
		return (free_new(new, *j));
	ft_strncpy(new[*j], old[i], ft_strlen(old[i]));
	*j += 1;
	return (new);
}

char	**remove_env(char **old, int n)
{
	char	**new;
	int		i;
	int		j;

	if (!old)
		return (NULL);
	new = malloc(sizeof(char *) * ft_tablen(old));
	if (!new)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (old && old[i])
	{
		if (i != n)
			if (!malloc_unset(old, new, i, &j))
				return (NULL);
		i++;
	}
	new[j] = NULL;
	free_tab(old);
	old = NULL;
	return (new);
}

int	del_env(char *str, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
		{
			g_global.data->shell.env = remove_env(env, i);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ms_unset(char *cmd, char **args, char **env)
{
	int		i;
	char	*str;

	if (ft_strcmp("unset", cmd))
		return (EXIT_FAILURE);
	i = 0;
	if (args[0][0] == '-')
		return (err_bd(-2, "minishell: unset: ", args[i]));
	str = NULL;
	while (args && args[i])
	{
		str = ft_strjoin(args[i], "=", 0);
		if (!str)
			return (EXIT_FAILURE);
		del_env(str, env);
		if (g_global.data->err)
		{
			free(str);
			return (EXIT_FAILURE);
		}
		free(str);
		i++;
	}
	return (EXIT_SUCCESS);
}
