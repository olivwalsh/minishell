/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:29:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 18:10:26 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd(char *cmd, char **args, char **env)
{
	char	*cwd;

	cwd = NULL;
	(void)env;
	if (ft_strcmp("cd", cmd))
		return (EXIT_FAILURE);
	if (args && args[1] && args[2])
		return (cd_error(-11, NULL));
	else
		return (cd_navigate(args[1], env));
	return (EXIT_SUCCESS);
}
