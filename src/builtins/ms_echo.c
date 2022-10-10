/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 16:18:49 by foctavia         ###   ########.fr       */
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
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
