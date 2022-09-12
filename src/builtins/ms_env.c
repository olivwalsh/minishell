/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/09 16:55:13 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_error(int code, char *arg)
{
	char	*str;

	str = NULL;
	if (code == -1)
	{
		str = ft_strjoin(str, "env: ", 1);
		str = ft_strjoin(str, arg, 1);
		str = ft_strjoin(str, ": No such file or directory", 1);
		printf("%s\n", str);
		free(str);
	}
	return (EXIT_FAILURE);
}

void	display_env(char **env)
{
	int	i;

	if (env)
	{
		i = 0;
		while (env && env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	else
		printf("no env\n");
}

int	ms_env(char *cmd, char **args, char **env)
{
	if (ft_strcmp("env", cmd))
		return (EXIT_FAILURE);
	if (args && args[0])
		return (ms_env_error(-1, args[0]));
	else
		display_env(env);
	return (EXIT_SUCCESS);
}
