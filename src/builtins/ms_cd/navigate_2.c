/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:43:51 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 18:10:09 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*pwd;

	pwd = ft_getenv("PWD");
	while (path && !ft_strncmp("../", path, 3))
	{
		nav_back(env);
		path += 3;
	}
	nav_relative(path, env);
	set_oldpwd(pwd, env);
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
			break ;
		i--;
	}
	new = ft_strncpy(new, pwd, i);
	if (chdir(new) < 0)
		return (EXIT_FAILURE);
	set_oldpwd(pwd, env);
	set_pwd(new, env);
	return (EXIT_SUCCESS);
}
