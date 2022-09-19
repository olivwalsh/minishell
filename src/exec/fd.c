/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:05:55 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 17:16:19 by owalsh           ###   ########.fr       */
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
	tmp = (*cmds)->next->next;
	if (tmp->cmd->fd_in == -1)
		tmp->cmd->fd_in = pipes[0];
	else
		close(pipes[0]);
	return (EXIT_SUCCESS);
}

int	update_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			exit(errno);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 0)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			exit(errno);
		close(cmd->fd_out);
	}
	return (EXIT_SUCCESS);
}

int	close_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	if (cmd->fd_out > 0)
		close(cmd->fd_out);
	return (EXIT_SUCCESS);
}