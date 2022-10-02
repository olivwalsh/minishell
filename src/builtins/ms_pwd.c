/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:59:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 16:34:51 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(char *cmd, char **args, char **env)
{
	char	*cwd;

	(void)args;
	(void)env;
	if (ft_strcmp(cmd, "pwd"))
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
