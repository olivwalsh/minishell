/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:28:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/29 11:04:36 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_error(int code)
{
	if (code == -1)
		printf("Too many args in function call\n");
	else if (code == -2)
		printf("Argument is not numeric\n");
}

int	check_flag(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ms_exit_error(-2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ms_exit(char *cmd, char **args)
{
	if (ft_strcmp("exit", cmd))
		return (EXIT_FAILURE);
	if (args && args[1])
	{
		ms_exit_error(-1);
		return (EXIT_FAILURE);
	}
	else if (args && args[0] && !check_flag(args[0]))
		exit(atoi(args[0]));
	else
		exit(EXIT_SUCCESS);
}
