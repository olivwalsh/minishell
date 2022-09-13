/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:52:25 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 18:08:04 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd or cd ~
int	nav_home(char **env)
{
	char	*home;

	home = ft_getenv("HOME");
	if (chdir(home) < 0)
		exit(errno);
	set_oldpwd(getenv("PWD"), env);
	set_pwd(home, env);
	return (EXIT_SUCCESS);
}

// cd relative/path
int	nav_relative(char *path, char **env)
{
	char	*pwd;

	if (!path)
		return (EXIT_FAILURE);
	pwd = ft_getenv("PWD");
	set_oldpwd(pwd, env);
	pwd = ft_strjoin(pwd, "/", 0);
	pwd = ft_strjoin(pwd, path, 1);
	if (chdir(pwd) < 0)
		return (cd_error(errno, path));
	set_pwd(pwd, env);
	return (EXIT_SUCCESS);
}

// cd /absolute/path
int	nav_absolute(char *path, char **env)
{
	char	*pwd;

	pwd = ft_getenv("PWD");
	set_oldpwd(pwd, env);
	if (chdir(path) < 0)
		return (cd_error(-12, path));
	set_pwd(path, env);
	return (EXIT_SUCCESS);
}

// cd ~/from/home/dir
int	nav_fromhome(char *path, char **env)
{
	nav_home(env);
	path++;
	return (nav_relative(++path, env));
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
