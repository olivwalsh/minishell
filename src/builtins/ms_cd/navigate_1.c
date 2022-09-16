/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:52:25 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/15 19:12:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd or cd ~
int	nav_home(char **env)
{
	char	*home;

	home = ft_getenv("HOME");
	if (chdir(home) < 0)
		return (cd_error(errno, home));
	set_pwd(home, env);
	return (EXIT_SUCCESS);
}

// cd relative/path
int	nav_relative(char *origin, char *path, char **env)
{
	origin = ft_strjoin(origin, "/", 0);
	origin = ft_strjoin(origin, path, 1);
	if (chdir(origin) < 0)
	{
		free(origin);
		return (cd_error(errno, path));
	}
	set_pwd(origin, env);
	return (EXIT_SUCCESS);
}

// cd ~/from/home/dir
int	nav_fromhome(char *path, char **env)
{
	char	*home;
	char	*pwd;

	home = ft_getenv("HOME");
	path++;
	pwd = ft_strjoin(home, "/", 1);
	pwd = ft_strjoin(pwd, path, 1);
	if (chdir(pwd) < 0)
		return (cd_error(errno, path));
	set_pwd(pwd, env);
	return (EXIT_SUCCESS);
}

int	cd_navigate(char *path, char **env)
{
	char	*pwd;
	int		error;

	error = 0;
	pwd = ft_getenv("PWD");
	if (!path || !path[0] || !ft_strcmp(path, "~"))
		error = nav_home(env);
	else if (!ft_strcmp(path, ".") || !ft_strcmp(path, "./"))
		error = nav_pwd(env);
	else if (!ft_strcmp(path, "-"))
		error = nav_oldpwd(env);
	else if (path[0] == '~' && path[1])
		error = nav_fromhome(path, env);
	else if (!ft_strcmp(path, ".."))
		error = nav_back(pwd, env);
	else if (!ft_strncmp("../", path, 3))
		error = nav_backwards(path, env);
	else if (is_absolute(path))
		error = nav_absolute(path, env);
	else
		error = nav_relative(pwd, path, env);
	if (error)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	set_oldpwd(pwd, env);
	return (EXIT_SUCCESS);
}
