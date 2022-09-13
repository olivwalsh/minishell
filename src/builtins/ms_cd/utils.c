/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:44:17 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 18:10:50 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_pwd(char *newpath, char **env)
{
	char	**path;

	path = malloc(sizeof(char *) * 2);
	if (!path)
		return (EXIT_FAILURE);
	path[0] = ft_strjoin("PWD=", newpath, 0);
	path[1] = NULL;
	return (ms_export("export", path, env));
}

int	set_oldpwd(char *newpath, char **env)
{
	char	**path;

	path = malloc(sizeof(char *) * 2);
	if (!path)
		return (EXIT_FAILURE);
	path[0] = ft_strjoin("OLDPWD=", newpath, 0);
	path[1] = NULL;
	return (ms_export("export", path, env));
}

int	is_absolute(char *path)
{
	if (path && path[0] == '/')
		return (1);
	return (0);
}
