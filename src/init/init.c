/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:14:01 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 14:37:32 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_init(t_data *data, char **argv, char **env, int *res)
{
	(void)argv;
	*res = 0;
	ft_memset(data, 0, sizeof(t_data));
	g_global.data = data;
	if (copy_env(data, env))
		return (EXIT_FAILURE);
	rl_catch_signals = 0;
	tcgetattr(STDIN_FILENO, &data->terminal.dftl);
	ft_memcpy(&data->terminal.new, \
		&data->terminal.dftl, sizeof(struct termios));
	ft_memcpy(&g_global.data->terminal.heredoc, \
		&g_global.data->terminal.dftl, sizeof(struct termios));
	data->terminal.new.c_cc[VEOF] = KEY_NONE;
	data->terminal.new.c_cc[VQUIT] = KEY_CTRL_D;
	data->terminal.new.c_cc[VMIN] = 150;
	data->terminal.heredoc.c_lflag &= ~(ECHOCTL);
	data->terminal.heredoc.c_cc[VINTR] = KEY_NONE;
	data->terminal.heredoc.c_cc[VQUIT] = KEY_CTRL_C;
	return (EXIT_SUCCESS);
}
