/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 16:05:55 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 11:18:11 by foctavia         ###   ########.fr       */
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
		if (cmds->cmd->pipe_out == -1)
			cmds->cmd->pipe_out = pipes[1];
		else
			close(pipes[1]);
		if (cmds->cmd->pipe_in == -1)
			cmds->cmd->pipe_in = pipes[0];
		else
			close(pipes[0]);
	}
	return (EXIT_SUCCESS);
}

int	redir_prevcmd(t_cmdlst *cmds)
{
	t_cmdlst	*tmp;

	tmp = cmds->prev;
	while (tmp && tmp->type != WORD)
		tmp = tmp->prev;
	if (tmp->cmd->pipe_in != -1)
	{
		if (dup2(tmp->cmd->pipe_in, STDIN_FILENO) < 0)
			exit(errno);
		close(tmp->cmd->pipe_in);
	}
	return (EXIT_SUCCESS);
}

int	redir_fd(t_cmdlst *cmds, t_cmd *cmd)
{
	if (cmd->pipe_in != -1)
		close(cmd->pipe_in);
	if (cmd->redir_out != -1)
	{
		if (dup2(cmd->redir_out, STDOUT_FILENO) < 0)
			exit(errno);
		close(cmd->redir_out);
	}
	else if (cmd->pipe_out != -1)
	{
		if (dup2(cmd->pipe_out, STDOUT_FILENO) < 0)
			exit(errno);
		close(cmd->pipe_out);
	}
	if (cmd->redir_in != -1)
	{
		if (dup2(cmd->redir_in, STDIN_FILENO) < 0)
			exit(errno);
		close(cmd->redir_in);
	}
	else if (cmds->prev)
		redir_prevcmd(cmds);
	return (EXIT_SUCCESS);
}

int	close_fd(t_cmdlst *cmds, t_cmd *cmd)
{
	t_cmdlst	*tmp;

	if (cmd->pipe_out != -1)
		close(cmd->pipe_out);
	else if (cmd->redir_out != -1)
		close(cmd->redir_out);
	if (cmd->redir_in != -1)
		close(cmd->redir_in);
	else if (cmds->prev)
	{
		tmp = cmds->prev;
		while (tmp && tmp->type != WORD)
			tmp = tmp->prev;
		if (tmp->cmd->pipe_in > 0)
			close(tmp->cmd->pipe_in);
	}
	return (EXIT_SUCCESS);
}
