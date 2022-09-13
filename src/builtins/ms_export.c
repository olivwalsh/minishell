/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:19 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/13 15:46:52 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*cut_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			str[i + 1] = '\0';
		i++;
	}
	return (str);
}

int	add_env(char *str, char **env)
{
	int		i;
	char	*new;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (err_msg(-2, 0));
	new = ft_strncpy(new, str, ft_strlen(str));
	str = cut_str(str);
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

int	args_checker(char **args, int i)
{
	int		j;
	char	*auth;

	j = 0;
	auth = "_=";
	if (args[i][j] == '-')
		return (err_bd(-2, "minishell: export: ", args[i]));
	while (args && args[i] && args[i][j])
	{
		if (!is_alpha(args[i][0]) && args[i][0] != '_' && args[i][0] != '/')
			return (err_bd(-3, "minishell: export: `", args[i]));
		if (!is_alnum(args[i][j]) && !strchr(auth, args[i][j]))
			return (err_bd(-3, "minishell: export: `", args[i]));
		if (args[i][j] == '=')
			auth = "_=/";
		j++;
	}
	return (EXIT_SUCCESS);
}

int	ms_export(char *cmd, char **args, char **env)
{
	int		i;

	i = 0;
	(void)cmd;
	display_env(env);
	if (!args || !args[0])
		display_export(env);
	while (args && args[i])
	{
		if (args_checker(args, i))
			return (EXIT_FAILURE);
		if (strchr(args[i], '=') && args[i][0] != '=')
			add_env(args[i], env);
		i++;
	}
	return (EXIT_SUCCESS);
}
