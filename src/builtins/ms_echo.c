/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 15:18:46 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_args(char **args, int i)
{
	write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
	if (args[i + 1])
		write(STDOUT_FILENO, " ", 1);
}

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
		write_args(args, i);
		i++;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
