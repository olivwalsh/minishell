/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:50 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/05 13:57:09 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmdpath(char *cmd)
{
	char	*path;
	char	*cmd_path;
	char	**path_list;
	int		i;

	path_list = ft_split(ft_getenv("PATH"), ':');
	if (!access(cmd, X_OK))
		return (cmd);
	i = 0;
	while (path_list && path_list[i])
	{
		path = ft_strjoin(path_list[i], "/", 0);
		cmd_path = ft_strjoin(path, cmd, 0);
		if (!access(cmd_path, X_OK))
		{
			free(path);
			free_tab(path_list);
			return (cmd_path);
		}
		i++;
		free(path);
		free(cmd_path);
	}
	free_tab(path_list);
	return (cmd);
}
