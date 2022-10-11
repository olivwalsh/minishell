/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 15:15:46 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_checker(char *cmd, char **path_list)
{
	int	err;

	err = 0;
	if (!ft_strncmp("..", cmd, 3))
		err = err_cmd(NO_CMD, cmd);
	if (!ft_strncmp(".", cmd, 2))
		err = err_cmd(FILE_ARG, cmd);
	if (err)
	{
		free_tab(path_list);
		free(cmd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	**get_pathlist(char *cmd)
{
	char	**path_list;
	char	*path;

	path = ft_getenv("PATH");
	if (!path)
	{
		err_cmd(NO_FILE, cmd);
		free(cmd);
		return (NULL);
	}
	path_list = ft_split(path, ':');
	free(path);
	return (path_list);
}

char	*get_access(char *cmd, char **path_list)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (path_list && path_list[i])
	{
		cmd_path = ft_strjoin(ft_strjoin(path_list[i++], "/", 0), cmd, 1);
		if (!access(cmd_path, X_OK))
		{
			free(cmd);
			free_tab(path_list);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free_tab(path_list);
	if (ft_strchr(cmd, '/'))
		err_cmd(NO_FILE, cmd);
	else
		err_cmd(NO_CMD, cmd);
	free(cmd);
	return (NULL);
}

char	*get_cmdpath(char *cmd)
{
	char	**path_list;

	path_list = get_pathlist(cmd);
	if (!path_list)
		return (NULL);
	if (cmd_checker(cmd, path_list))
		return (NULL);
	if (!access(cmd, X_OK))
	{
		free_tab(path_list);
		return (cmd);
	}
	return (get_access(cmd, path_list));
}
