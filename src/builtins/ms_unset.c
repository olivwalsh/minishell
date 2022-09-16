/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:23 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/14 17:10:20 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			new[j++] = old[i++];
		else if (i == n)
			free(old[i++]);
	}
	new[j] = NULL;
	free(old);
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
