/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 09:59:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 10:04:09 by owalsh           ###   ########.fr       */
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
		return (EXIT_FAILURE);
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
