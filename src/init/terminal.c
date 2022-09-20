/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:57:12 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/20 16:55:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_exit(int signum)
{
	(void)signum;
	write(2, "exit", 4);
	tcsetattr(0, TCSANOW, &g_global.data->terminal.dftl);
	clean(g_global.data);
	rl_clear_history();
	exit(0);
}

void	sig_nl(int signum)
{
	(void)signum;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_terminal(void)
{
	struct termios dflt;
	struct termios new;
	
	dflt = g_global.data->terminal.dftl;
	new = g_global.data->terminal.new;
	tcgetattr(STDIN_FILENO, &dflt);
	memcpy(&new, &dflt, sizeof(struct termios));
	// sigaction()
    signal(SIGQUIT, &sig_exit);
    signal(SIGINT, &sig_nl);
	new.c_cc[VINTR] = 3;
    new.c_cc[VQUIT] = 0;
    new.c_cc[VEOF] = 34;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}
