/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:19 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/10 08:47:48 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_export_error(int code, char *arg)
{
	char	*str;

	str = NULL;
	if (code == -1)
	{
		str = ft_strjoin(str, "minishell: export: ", 1);
		str = ft_strjoin(str, arg, 1);
		str = ft_strjoin(str, ": Invalid option", 1);
		printf("%s\n", str);
		free(str);
	}
	else if (code == -2)
	{
		str = ft_strjoin(str, "minishell: export: `", 1);
		str = ft_strjoin(str, arg, 1);
		str = ft_strjoin(str, "': not a valid identifier", 1);
		printf("%s\n", str);
		free(str);
	}
	return (EXIT_FAILURE);
}

char	**free_new(char **str, int i)
{
	while (i >= 0)
		free(str[i--]);
	free(str);
	err_msg(-2, 0);
	return (NULL);
}

char	**redo_malloc(char **old, char *str, int n)
{
	char	**new;
	int		i;

	if (!str || !old || !n)
		return (NULL);
	new = malloc(sizeof(char *) * (n + 1));
	if (!new)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	i = 0;
	while (old && old[i])
	{
		new[i] = malloc(sizeof(char) * (ft_strlen(old[i]) + 1));
		if (!new[i])
			return (free_new(new, i));
		ft_strncpy(new[i], old[i], ft_strlen(old[i]));
		i++;
	}
	new[i] = str;
	new[i + 1] = NULL;
	free_tab(old);
	old = NULL;
	return (new);
}

int	add_env(char *str, char **env)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (err_msg(-2, 0));
	new = ft_strncpy(new, str, ft_strlen(str));
	while (str && str[i])
	{
		if (str[i] == '=')
			str[i + 1] = '\0';
		i++;
	}
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
		{
			free(env[i]);
			env[i] = new;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	g_global.data->shell.env = redo_malloc(env, new, i + 1);
	return (EXIT_SUCCESS);
}

int	ms_export(char *cmd, char **args, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		if (args[i][0] == '-')
			return (ms_export_error(-1, args[i]));
		while (args[i] && args[i][j])
		{
			if ((args[i][0] < 'A' || args[i][0] > 'Z') && \
				(args[i][0] < 'a' || args[i][0] > 'z') && args[i][0] != '_')
				return (ms_export_error(-2, args[i]));
			if ((args[i][j] < 'A' || args[i][j] > 'Z') && \
				(args[i][j] < 'a' || args[i][j] > 'z') && \
				(args[i][j] < '0' || args[i][j] > '9') && \
				args[i][j] != '_' && args[i][j] != '=')
				return (ms_export_error(-2, args[i]));
			j++;
		}
		if (strchr(args[i], '=') && args[i][0] != '=')
			add_env(args[i], env);
		i++;
	}
	return (EXIT_SUCCESS);
}
