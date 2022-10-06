/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 18:45:38 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmdpath(char *cmd)
{
	char	*cmd_path;
	char	**path_list;
	char	*env;
	int		i;

	env = ft_getenv("PATH");
	if (!env)
	{
		err_cmd(NO_FILE, cmd);
		return(NULL);
	}
	path_list = ft_split(env, ':');
	free(env);
	if (!ft_strncmp("..", cmd, 3))
	{
		err_cmd(NO_CMD, cmd);
		return (NULL);
	}
	if (!access(cmd, X_OK))
		return (cmd);
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
	err_cmd(NO_CMD, cmd);
	return (NULL);
}
