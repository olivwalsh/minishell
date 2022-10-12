/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:43:51 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/12 11:09:12 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cd . ou cd ./
int	nav_pwd(char **env)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (chdir(pwd) < 0)
	{
		free(pwd);
		return (err_bd(0, errno, "minishell: cd: ", pwd));
	}
	set_pwd(env);
	free(pwd);
	return (EXIT_SUCCESS);
}

// cd - -> navigate to oldpwd
int	nav_oldpwd(char **env)
{
	char	*oldpwd;

	oldpwd = ft_getenv("OLDPWD");
	if (chdir(oldpwd) < 0)
	{
		free(oldpwd);
		return (err_bd(0, errno, "minishell: cd: ", oldpwd));
	}
	set_pwd(env);
	free(oldpwd);
	return (EXIT_SUCCESS);
}

int	nav_absolute(char *path, char **env)
{
	if (chdir(path) < 0)
		return (err_bd(0, errno, "minishell: cd: ", path));
	set_pwd(env);
	return (EXIT_SUCCESS);
}
