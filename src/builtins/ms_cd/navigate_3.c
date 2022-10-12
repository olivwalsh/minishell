/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:08:38 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/12 11:08:58 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prev_dir(char *origin, int i)
{
	while (origin && i && origin[i])
	{
		if (origin[i] == '/')
			break ;
		i--;
	}
	if (!i)
		i = 1;
	return (i);
}

// cd ..
int	nav_back(char **env)
{
	char	*origin;
	char	*new;
	int		i;

	origin = NULL;
	origin = getcwd(origin, 0);
	if (ft_strlen(origin) == 1)
		return (nav_free(origin, EXIT_SUCCESS));
	i = ft_strlen(origin) - 1;
	if (origin[i] == '/')
		origin[i--] = '\0';
	new = malloc(sizeof(char) * ft_strlen(origin));
	if (!new)
		return (nav_free(origin, EXIT_FAILURE));
	i = prev_dir(origin, i);
	new = ft_strncpy(new, origin, i);
	chdir(new);
	set_pwd(env);
	free(new);
	return (nav_free(origin, EXIT_SUCCESS));
}

int	nav_fail(char *oldpwd, char *pwd)
{
	if (chdir(oldpwd) < 0)
	{
		free(oldpwd);
		free(pwd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	move_path(char **path, char **env, int i)
{
	nav_back(env);
	(*path) += i;
}

// cd ../../relative/path
int	nav_backwards(char *path, char **env)
{
	char	*oldpwd;
	char	*pwd;
	int		res;

	res = EXIT_SUCCESS;
	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, 0);
	while (path && !ft_strncmp("../", path, 3))
		move_path(&path, env, 3);
	if (!path || !path[0]
		|| !ft_strncmp(path, ".", 2) || !ft_strncmp(path, "./", 3))
		return (nav_free(oldpwd, EXIT_SUCCESS));
	if (!ft_strncmp(path, "..", 3))
		move_path(&path, env, 2);
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (path && path[0])
		res = nav_relative(pwd, path, env);
	if (res && nav_fail(oldpwd, pwd))
		return (res);
	free(oldpwd);
	return (nav_free(pwd, res));
}
