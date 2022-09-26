/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:14:01 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/26 15:40:59 by owalsh           ###   ########.fr       */
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
	
	// init readline defaults (GNU readline)
	rl_catch_signals = 0;
	
	// init terminal
	tcgetattr(STDIN_FILENO, &data->terminal.dftl);
	// set defaults
	memcpy(&data->terminal.new, &data->terminal.dftl, sizeof(struct termios));
	
	/* default
		CTRL-D => VEOF
		CTRL-C => VINTR
		CTRL-\ => VQUIT
	*/

	// altering terminal 
	data->terminal.new.c_cc[VEOF] = KEY_NONE;
    data->terminal.new.c_cc[VQUIT] = KEY_CTRL_D;
	
	/* minishell
		CTRL-D => VQUIT
		CTRL-C => VINTR
		CTRL-\ => NONE
	*/
	
	return (EXIT_SUCCESS);
}
