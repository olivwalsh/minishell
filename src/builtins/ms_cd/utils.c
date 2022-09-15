/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:44:17 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/15 17:31:21 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_pwd(char *newpath, char **env)
{
	char	**path;
	int		res;

	res = EXIT_SUCCESS;
	path = malloc(sizeof(char *) * 2);
	if (!path)
		return (EXIT_FAILURE);
	path[0] = ft_strjoin("PWD=", newpath, 0);
	path[1] = NULL;
	res = ms_export("export", path, env);
	free(newpath);
	free(path[0]);
	free(path[1]);
	free(path);
	return (res);
}

int	set_oldpwd(char *newpath, char **env)
{
	char	**path;
	int		res;

	res = EXIT_SUCCESS;
	path = malloc(sizeof(char *) * 2);
	if (!path)
		return (EXIT_FAILURE);
	path[0] = ft_strjoin("OLDPWD=", newpath, 0);
	path[1] = NULL;
	res = ms_export("export", path, env);
	free(newpath);
	free(path[0]);
	free(path[1]);
	free(path);
	return (res);
}

int	is_absolute(char *path)
{
	if (path && path[0] == '/')
		return (1);
	return (0);
}
