/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:58:19 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 18:02:01 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_eof(char *delimiter)
{
	write(2, "minishell: ", 11);
	write(2, "warning: here-document delimited by end-of-file (wanted `", 57);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
}

void	sig_prompt(int signum)
{
	(void)signum;
	if (g_global.data->shell.heredoc == 1)
	{
		if (g_global.data->shell.pid_heredoc == 0)
		{	
			close(g_global.data->shell.fd_heredoc[0]);
			write (0, "\n", 1);
			exit(EXIT_SUCCESS);
		}
	}
}

void	set_heredocterm(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global.data->terminal.heredoc);
	signal(SIGQUIT, &sig_prompt);
}
