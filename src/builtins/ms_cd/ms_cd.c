/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:29:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 15:09:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(char *cmd, char **args, char **env)
{
	int		res;
	char	*pwd;

	res = EXIT_SUCCESS;
	(void)cmd;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	if (args && args[1] && args[2])
		return (err_bd(TOO_MANY_ARGS, 0, "minishell: cd", NULL));
	else
		res = cd_navigate(args[1], env, pwd);
	if (res)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	set_oldpwd(pwd, env);
	free(pwd);
	return (res);
}
