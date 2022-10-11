/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 13:57:12 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 11:48:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_exit(int signum)
{
	(void)signum;
	if (rl_line_buffer[0])
		return ;
	write(1, "exit\n", 5);
	rl_clear_history();
	clean(g_global.data);
	exit(EXIT_SUCCESS);
}

void	sig_nl(int signum)
{
	(void)signum;
	write(1, "^C\n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_terminal(t_terminal *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new);
	signal(SIGQUIT, &sig_exit);
	signal(SIGINT, &sig_nl);
}
