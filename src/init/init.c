/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:14:01 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 19:00:02 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_init(t_data *data, char **argv, char **env)
{
	(void)argv;
	memset(data, 0, sizeof(t_data));
	g_global.data = data;
	if (copy_env(data, env))
		return (EXIT_FAILURE);
	rl_catch_signals = 0;
	tcgetattr(STDIN_FILENO, &data->terminal.dftl);
	memcpy(&data->terminal.new, &data->terminal.dftl, sizeof(struct termios));
	memcpy(&g_global.data->terminal.heredoc, \
		&g_global.data->terminal.dftl, sizeof(struct termios));
	data->terminal.new.c_cc[VEOF] = KEY_NONE;
	data->terminal.new.c_cc[VQUIT] = KEY_CTRL_D;
	data->terminal.new.c_cc[VMIN] = 150;
	data->terminal.heredoc.c_lflag &= ~(ECHOCTL);
	data->terminal.heredoc.c_cc[VINTR] = KEY_NONE;
	data->terminal.heredoc.c_cc[VQUIT] = KEY_CTRL_C;
	return (EXIT_SUCCESS);
}
