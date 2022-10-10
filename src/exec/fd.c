/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:05:55 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 18:45:12 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd(t_cmdlst *cmds)
{
	int	pipes[2];
	
	if (!cmds->next)
		return (EXIT_SUCCESS);
	else
	{
		if (pipe(pipes) < 0)
			exit(errno);
		if (cmds->cmd->fd_out == -1)
			cmds->cmd->fd_out = pipes[1];
		else
			close(pipes[1]);
		if (cmds->cmd->fd_in == -1)
			cmds->cmd->fd_in = pipes[0];
		else
			close(pipes[0]);
	}
	return (EXIT_SUCCESS);
}

int	redir_fd(t_cmdlst *cmds, t_cmd *cmd)
{
	t_cmdlst	*tmp;

	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
			exit(errno);
		close(cmd->fd_out);
	}
	if (cmd->redir && cmd->redir->redir_in && cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
			exit(errno);
	}
	else if (cmds->prev)
	{	
		tmp = cmds->prev;
		while (tmp && tmp->type != WORD)
			tmp = tmp->prev;
		if (tmp->cmd->fd_in > 0)
		{
			if (dup2(tmp->cmd->fd_in, STDIN_FILENO) < 0)
				exit(errno);
			close(tmp->cmd->fd_in);
		}
	}
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	return (EXIT_SUCCESS);
}

int	close_fd(t_cmdlst *cmds, t_cmd *cmd)
{
	t_cmdlst	*tmp;
	
	if (cmd->fd_out > 0)
		close(cmd->fd_out);
	if (cmd->redir && cmd->redir->redir_in && cmd->fd_in > 0)
		close(cmd->fd_in);
	else if (cmds->prev)
	{
		tmp = cmds->prev;
		while (tmp && tmp->type != WORD)
			tmp = tmp->prev;
		if (tmp->cmd->fd_in > 0)
			close(tmp->cmd->fd_in);
	}
	return (EXIT_SUCCESS);
}