/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:28:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 14:36:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (err_bd(NUM_ARG, 0, "exit\nminishell: exit: ", arg));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	clean_exit(char **env)
{
	struct termios	dflt;

	tcgetattr(STDIN_FILENO, &dflt);
	if (env)
		free_tab(env);
	return (EXIT_SUCCESS);
}

int	ms_exit(char *cmd, char **args, char **env)
{
	if (ft_strncmp("exit", cmd, 5))
		return (EXIT_FAILURE);
	if (args && args[0] && args[1])
		return (err_bd(TOO_MANY_ARGS, 0, "exit\nminishell: exit", NULL));
	if (args && args[0] && !check_flag(args[0]))
		exit(ft_atoi(args[0]));
	else
		exit(clean_exit(env));
}
