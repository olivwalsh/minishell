/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/31 15:37:00 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmdpath(char *cmd)
{
	char	*path;
	char	*cmd_path;
	char	**path_list;
	int		i;

	path_list = ft_split(getenv("PATH"), ':');
	if (!access(cmd, X_OK))
		return (cmd);
	i = 0;
	while (path_list && path_list[i])
	{
		path = ft_strjoin(path_list[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		if (!access(cmd_path, X_OK))
		{
			free(path);
			printf("returning cmd path = %s\n", cmd_path);
			return (cmd_path);
		}
		i++;
		free(path);
		free(cmd_path);
	}
	return (NULL);
}
