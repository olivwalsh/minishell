/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:29:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 19:50:54 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(char *pwd)
{
	free(pwd);
	return (EXIT_FAILURE);
}

int	ms_cd(char *cmd, char **args, char **env)
{
	int		res;
	char	*pwd;

	res = EXIT_SUCCESS;
	(void)cmd;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (cd_error(pwd));
	if (args && args[1] && args[2])
	{
		free(pwd);
		return (err_bd(TOO_MANY_ARGS, 0, "minishell: cd", NULL));
	}
	else
		res = cd_navigate(args[1], env, pwd);
	if (res)
		return (cd_error(pwd));
	set_oldpwd(pwd, env);
	free(pwd);
	return (res);
}
