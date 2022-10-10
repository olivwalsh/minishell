/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:44:17 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 14:10:38 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_pwd(char **env)
{
	char	**path;
	int		res;
	char	*cwd;

	res = EXIT_SUCCESS;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		free(cwd);
	path = malloc(sizeof(char *) * 2);
	if (!path)
		return (EXIT_FAILURE);
	path[0] = ft_strjoin("PWD=", cwd, 0);
	path[1] = NULL;
	res = ms_export("export", path, env);
	free(path[0]);
	free(path[1]);
	free(path);
	free(cwd);
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
