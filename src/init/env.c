/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:56:15 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/06 16:52:21 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_substr(char **env)
{
	int	i;
	
	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

static void	free_str(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
}

int	copy_substr(char **new_env, char **env, int substr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(env[i] && j < substr)
	{
		new_env[j] = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
		if (!new_env[j])
		{
			free_str(new_env, j);
			return (err_msg(-2, 0));
		}
		ft_strncpy(new_env[j], env[i], ft_strlen(env[i]));
		j++;
		i++;
	}
	new_env[substr] = NULL;
	return (EXIT_SUCCESS);
}

int	copy_env(t_data *data, char **env)
{
	char	**new_env;
	int		substr;
	int		i;

	i = 0;
	substr = 0;
	if (!env || !env[i] || !data)
		return (EXIT_FAILURE);
	substr = count_substr(env);
	if (!substr)
		return (EXIT_FAILURE);
	new_env = malloc(sizeof(char *) * (substr + 1));
	if (!new_env)
		return (err_msg(-2, 0));
	if (copy_substr(new_env, env, substr))
		return (EXIT_FAILURE);
	data->shell.env = new_env;
	return (EXIT_SUCCESS);
}