/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:59:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 18:43:10 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(char *cmd, char **args, char **env)
{
	char	*cwd;

	(void)args;
	(void)env;
	if (ft_strncmp(cmd, "pwd", 4))
		return (EXIT_FAILURE);
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
	{
		free(cwd);
		return (err_bd(0, errno, "pwd: ", NULL));
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
