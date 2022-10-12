/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:52:25 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/12 10:47:16 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd or cd ~
int	nav_home(char **env)
{
	char	*home;

	home = ft_getenv("HOME");
	if (!home)
		return (err_bd(NO_HOME, 0, "minishell: cd", NULL));
	if (chdir(home) < 0)
	{
		free(home);
		return (err_bd(NO_HOME, 0, "minishell: cd", NULL));
	}
	set_pwd(env);
	free(home);
	return (EXIT_SUCCESS);
}

// cd relative/path
int	nav_relative(char *origin, char *path, char **env)
{
	if (origin && origin[ft_strlen(origin) - 1] != '/')
	{
		origin = ft_strjoin(origin, "/", 0);
		origin = ft_strjoin(origin, path, 1);
	}
	else
		origin = ft_strjoin(origin, path, 0);
	if (chdir(origin) < 0)
	{
		free(origin);
		return (err_bd(0, errno, "minishell: cd: ", path));
	}
	set_pwd(env);
	free(origin);
	return (EXIT_SUCCESS);
}

// cd ~/from/home/dir
int	nav_fromhome(char *path, char **env)
{
	char	*home;
	char	*pwd;

	home = ft_getenv("HOME");
	if (!home)
		return (err_bd(NO_HOME, 0, "minishell: cd", NULL));
	path++;
	pwd = ft_strjoin(home, "/", 1);
	pwd = ft_strjoin(pwd, path, 1);
	if (chdir(pwd) < 0)
	{
		free(pwd);
		return (err_bd(0, errno, "minishell: cd: ", path));
	}
	set_pwd(env);
	free(pwd);
	return (EXIT_SUCCESS);
}

int	cd_navigate(char *path, char **env, char *pwd)
{
	int		error;

	error = 0;
	if (!path || !path[0] || !ft_strncmp(path, "~", 2))
		error = nav_home(env);
	else if (!ft_strncmp(path, ".", 2) || !ft_strncmp(path, "./", 3))
		return (EXIT_SUCCESS);
	else if (!ft_strncmp(path, "-", 2))
		error = nav_oldpwd(env);
	else if (path[0] == '~' && path[1])
		error = nav_fromhome(path, env);
	else if (!ft_strncmp(path, "..", 3))
		error = nav_back(env);
	else if (!ft_strncmp("../", path, 3))
		error = nav_backwards(path, env);
	else if (is_absolute(path))
		error = nav_absolute(path, env);
	else
		error = nav_relative(pwd, path, env);
	return (error);
}
