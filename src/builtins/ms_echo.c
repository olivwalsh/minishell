/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/09 11:27:03 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(char *cmd, char **args)
{
	int	i;

	if (ft_strcmp(cmd, "echo"))
		return (EXIT_FAILURE);
	i = 1;
	while (args && args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	printf("\n");
	return (EXIT_SUCCESS);
}
