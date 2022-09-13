/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:52:25 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 17:03:07 by owalsh           ###   ########.fr       */
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

// cd ..
int	nav_back(char **env)
{
	char	*pwd;
	char	*new;
	int		i;

	pwd = ft_getenv("PWD");
	i = ft_strlen(pwd) - 1;
	if (pwd[i] == '/')
		pwd[i--] = '\0';
	new = malloc(sizeof(char) * ft_strlen(pwd));
	if (!new)
		return (EXIT_FAILURE);
	while (pwd && i && pwd[i])
	{
		if (pwd[i] == '/')
			break;
		i--;
	}
	new = ft_strncpy(new, pwd, i);
	if (chdir(new) < 0)
		return (EXIT_FAILURE);
	set_oldpwd(pwd, env);
	set_pwd(new, env);
	return (EXIT_SUCCESS);
}

// cd relative/path
int	nav_relative(char *path, char **env)
{
	char	*pwd;

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

// cd - -> navigate to oldpwd
int	nav_oldpwd(char **env)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD");
	pwd = ft_getenv("PWD");
	set_oldpwd(pwd, env);
	if (chdir(oldpwd) < 0)
		return (EXIT_FAILURE);
	set_pwd(pwd, env);
	return (EXIT_SUCCESS);
}

// cd ../../relative/path
int	nav_backwards(char *path, char **env)
{
	while (path && !ft_strncmp("../", path, 3))
	{
		nav_back(env);
		path += 3;
	}
	return (nav_relative(path, env));
}
