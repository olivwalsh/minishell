/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:28:02 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/26 15:19:23 by owalsh           ###   ########.fr       */
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

// void	exit_terminal(void)
// {
// 	struct termios dflt;
	
// 	tcgetattr(STDIN_FILENO, &dflt);
	
// 	dflt = g_global.data->terminal.dftl;
// 	dflt.c_cc[VINTR] = KEY_CTRLC;
// 	dflt.c_cc[VEOF] = KEY_CTRLD;
// 	dflt.c_cc[VINTR] = KEY_CTRLQ;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &dflt);
// }

int	clean_exit(char **env)
{
	struct termios dflt;
	
	tcgetattr(STDIN_FILENO, &dflt);
	if (env)
	{
		if (env)
			free_tab(env);
	}
	// exit_terminal();
	return (EXIT_SUCCESS);
}

int	ms_exit(char *cmd, char **args, char **env)
{
	if (ft_strcmp("exit", cmd))
		return (EXIT_FAILURE);
	if (args && args[0])
	{
		ms_exit_error(-1);
		return (EXIT_FAILURE);
	}
	else if (args && args[0] && !check_flag(args[0]))
		exit(atoi(args[0]));
	else
		exit(clean_exit(env));
}
