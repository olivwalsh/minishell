/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 14:45:21 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*path_found(char *cmd, char **path_list, char *cmd_path)
{
	free(cmd);
	free_tab(path_list);
	return (cmd_path);
}

static char	*err_nocmd(char *cmd)
{
	err_cmd(NO_CMD, cmd);
	return (NULL);
}

static char	*err_env(char *cmd)
{
	err_cmd(NO_FILE, cmd);
	return (NULL);
}

char	*get_cmdpath(char *cmd)
{
	char	*cmd_path;
	char	**path_list;
	char	*env;
	int		i;

	env = ft_getenv("PATH");
	if (!env)
		return (err_env(cmd));
	path_list = ft_split(env, ':');
	free(env);
	if (!ft_strncmp("..", cmd, 3))
		return (err_nocmd(cmd));
	if (!access(cmd, X_OK))
		return (cmd);
	i = 0;
	while (path_list && path_list[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(path_list[i++], "/", 0), cmd, 1);
		if (!access(cmd_path, X_OK))
			return (path_found(cmd, path_list, cmd_path));
		free(cmd_path);
	}
	free_tab(path_list);
	err_cmd(NO_CMD, cmd);
	return (NULL);
}
