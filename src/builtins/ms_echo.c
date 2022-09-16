/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 16:19:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(char *cmd, char **args)
{
	int	i;
	int	nl;

	nl = 1;
	if (ft_strcmp("echo", cmd))
		return (EXIT_FAILURE);
	i = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		i = 2;
		nl = 0;
	}
	while (args && args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	if (nl)
		printf("\n");
	return (EXIT_SUCCESS);
}
