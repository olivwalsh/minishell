/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:23 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/06 18:44:47 by owalsh           ###   ########.fr       */
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
		err_msg_str(MALLOC_ERR);
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

int	unset_checker(char **args, int i)
{
	int		j;

	j = 1;
	if (!args[i][0])
		return (err_bd(NO_ID, 0, "minishell: unset: `", args[i]));
	if (args[i][0] == '-')
		return (err_bd(NO_OPTION, 0, "minishell: unset: ", args[i]));
	if (!is_alpha(args[i][0]) && args[i][0] != '_' && args[i][0] != '\\')
		return (err_bd(NO_ID, 0, "minishell: unset: `", args[i]));
	while (args && args[i] && args[i][j])
	{
		if (!is_alnum(args[i][j]) && args[i][j] != '_' && args[i][j] != '\\')
			return (err_bd(NO_ID, 0, "minishell: unset: `", args[i]));
		j++;
	}
	return (EXIT_SUCCESS);
}

int	ms_unset(char *cmd, char **args, char **env)
{
	int		i;
	char	*str;

	if (ft_strncmp("unset", cmd, 6))
		return (EXIT_FAILURE);
	i = 0;
	str = NULL;
	while (args && args[i])
	{
		if (!unset_checker(args, i))
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
		}
		i++;
	}
	if (g_global.data->err)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
