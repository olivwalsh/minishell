/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:43:51 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/15 18:02:59 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd . ou cd ./
int	nav_pwd(char **env)
{
	char	*pwd;

	pwd = ft_getenv("PWD");
	if (chdir(pwd) < 0)
		return (cd_error(errno, pwd));
	set_pwd(pwd, env);
	return (EXIT_SUCCESS);
}

// cd - -> navigate to oldpwd
int	nav_oldpwd(char **env)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD");
	if (chdir(oldpwd) < 0)
		return (cd_error(errno, oldpwd));
	set_pwd(oldpwd, env);
	return (EXIT_SUCCESS);
}

// cd ..
int	nav_back(char *origin, char **env)
{
	char	*new;
	int		i;

	i = ft_strlen(origin);
	if (i == 1)
		return (EXIT_SUCCESS);
	i--;
	if (origin[i] == '/')
		origin[i--] = '\0';
	new = malloc(sizeof(char) * ft_strlen(origin));
	if (!new)
		return (EXIT_FAILURE);
	while (origin && i && origin[i])
	{
		if (origin[i] == '/')
			break ;
		i--;
	}
	if (!i)
		i = 1;
	new = ft_strncpy(new, origin, i);
	chdir(new);
	set_pwd(new, env);
	return (EXIT_SUCCESS);
}

// cd ../../relative/path
int	nav_backwards(char *path, char **env)
{
	char	*pwd;
	int		res;

	res = EXIT_SUCCESS;
	pwd = NULL;
	while (path && !ft_strncmp("../", path, 3))
	{
		pwd = ft_getenv("PWD");
		nav_back(pwd, env);
		free(pwd);
		path += 3;
	}
	if (!path || !path[0])
		return (EXIT_SUCCESS);
	if (!ft_strcmp(path, ".") || !ft_strcmp(path, "./"))
		return (nav_pwd(env));
	pwd = ft_getenv("PWD");
	res = nav_relative(pwd, path, env);
	free(pwd);
	return (res);
}

int	nav_absolute(char *path, char **env)
{
	if (chdir(path) < 0)
		return (cd_error(errno, path));
	set_pwd(path, env);
	return (EXIT_SUCCESS);
}