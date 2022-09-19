/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:57:12 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/19 18:48:51 by owalsh           ###   ########.fr       */
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
	printf("newline\n");
}

void	init_terminal(void)
{
	struct termios dflt;
	struct termios new;
	
	dflt = g_global.data->terminal.dftl;
	new = g_global.data->terminal.new;
	tcgetattr(STDIN_FILENO, &dflt);
	// printf("Ctrl-C : dflt.c_cc[VINTR] = %d\n", dflt.c_cc[VINTR]);
	// printf("Ctrld-D: dflt.c_cc[VEOF] = %d\n", dflt.c_cc[VEOF]);
	// printf("Ctrl-\\ dflt.c_cc[VQUIT] = %d\n", dflt.c_cc[VQUIT]);
	memcpy(&new, &dflt, sizeof(struct termios));
	// signal(SIGINT, &sig_nl);
	new.c_cc[VINTR] = 4;
    new.c_cc[VQUIT] = 0;
    new.c_cc[VEOF] = 34;
    // signal(SIGQUIT, &sig_exit);
    signal(SIGINT, &sig_exit);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	// g_global.data->terminal.new = new;
	// change attributes as required
	// manage signals
}
