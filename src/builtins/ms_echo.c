/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/04 11:52:55 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(char *cmd, char **args)
{
	int	i;
	int	j;
	int	nl;

	nl = TRUE;
	i = 0;
	(void)cmd;
	while (args[++i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] && args[i][j] == 'n')
			j++;
		if (args[i][j])
			break ;
		nl = FALSE;
	}
	while (args && args[i])
		printf("%s ", args[i++]);
	if (nl)
		printf("\n");
	return (EXIT_SUCCESS);
}
