/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:59:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 13:52:01 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_error(int err)
{
	write(2, "pwd: ", 5);
	if (err == -7)
		write(2, "too many arguments", 18);
	else
	{
		write(2, "error retrieving current directory: getcwd: ", 49);
		write(2, strerror(err), ft_strlen(strerror(err)));
	}
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

int	ms_pwd(char *cmd, char **args, char **env)
{
	char	*cwd;

	(void)args;
	(void)env;
	if (ft_strcmp(cmd, "pwd"))
		return (EXIT_FAILURE);
	if (args && args[1])
		return (pwd_error(-7));
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (pwd_error(errno));
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
