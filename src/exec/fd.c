/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:05:55 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 12:29:19 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd(t_cmdlst **cmds)
{
	int			pipes[2];
	t_cmdlst	*tmp;

	if (pipe(pipes) < 0)
		exit(errno);
	if ((*cmds)->cmd->fd_out == -1)
		(*cmds)->cmd->fd_out = pipes[1];
	else
		close(pipes[1]);
	tmp = (*cmds)->next;
	while (tmp && tmp->type != WORD)
		tmp = tmp->next;
	if (tmp->cmd->fd_in == -1)
		tmp->cmd->fd_in = pipes[0];
	else
		close(pipes[0]);
	return (EXIT_SUCCESS);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	n %= 10;
	n += 48;
	write (fd, &n, 1);
}

int	update_fd(t_cmd *cmd)
{
	int	res_in;
	int	res_out;

	res_in = -2;
	res_out = -2;
	if (cmd->fd_out > 2)
	{
		res_out = dup2(cmd->fd_out, STDOUT_FILENO);
		if (res_out < 0)
			exit(errno);
		close(cmd->fd_out);
	}
	if (cmd->fd_in > 2)
	{
		res_in = dup2(cmd->fd_in, STDIN_FILENO);
		if (res_in < 0)
			exit(errno);
		close(cmd->fd_in);
	}
	return (EXIT_SUCCESS);
}

int	close_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	return (EXIT_SUCCESS);
}
