/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:29:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 17:04:38 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(int err, char *path)
{
	write(2, "minishell: ", 11);
	if (err == -11)
		write(2, "too many arguments in function call.", 36);
	else if (err == ENOENT)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory", 28);
	}
	else if (err == ENOTDIR)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": Not a directory", 17);
	}
	else if (err == EACCES)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied", 19);
	}
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

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

int	cd_navigate(char *path, char **env)
{
	int	i;

	i = 0;
	if (!path || !path[0] || !ft_strcmp(path, "~"))
		return (nav_home(env));
	else if (!ft_strcmp(path, "-"))
		return (nav_oldpwd(env));
	else if (path[0] == '~' && path[1])
		return (nav_fromhome(path, env));
	else if (!ft_strcmp(path, ".."))
		return (nav_back(env));
	else if (!ft_strncmp("../", path, 3))
		return (nav_backwards(path, env));
	else if (is_absolute(path))
		return (nav_absolute(path, env));
	else
		return (nav_relative(path, env));
	return (EXIT_FAILURE);
}

int	ms_cd(char *cmd, char **args, char **env)
{
	char	*cwd;

	cwd = NULL;
	(void)env;
	if (ft_strcmp("cd", cmd))
		return (EXIT_FAILURE);
	if (args && args[1] && args[2])
		return (cd_error(-11, NULL));
	else return (cd_navigate(args[1], env));
	return (EXIT_SUCCESS);
}
