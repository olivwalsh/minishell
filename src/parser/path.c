/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/08 16:40:31 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_error(char *cmd)
{
	write(1, "command not found: ", 19);
	while (cmd && *cmd && *cmd != ' ')
	{		
		write(1, cmd, 1);
		cmd++;
	}
	write(1, "\n", 1);
	return (0);
}

char	*get_cmdpath(char *cmd)
{
	char	*cmd_path;
	char	**path_list;
	char	*env;
	int		i;

	env = ft_getenv("PATH");
	path_list = ft_split(env, ':');
	free(env);
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
	command_error(cmd);
	return (cmd);
}
