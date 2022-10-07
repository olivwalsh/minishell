/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:05:55 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/07 18:03:58 by foctavia         ###   ########.fr       */
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

int	update_fd(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
	{
		printf("in update fd_in is %d, in pid: %d\n", cmd->fd_in, getpid());
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			exit(errno);
		close(cmd->fd_in);
		printf("in close fd_in is %d, in pid: %d\n", cmd->fd_in, getpid());
	}
	if (cmd->fd_out > 0)
	{
		printf("in update fd_out is %d, in pid: %d\n", cmd->fd_out, getpid());
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			exit(errno);
		close(cmd->fd_out);
		printf("in close fd_out is %d, in pid: %d\n", cmd->fd_out, getpid());
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
