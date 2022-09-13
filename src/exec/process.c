/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:47:30 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 09:29:33 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin(t_cmd *cmd, char **env)
{
	if (cmd->builtin == BD_EXIT)
		ms_exit(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_ENV)
		ms_env(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_ECHO)
		ms_echo(cmd->cmd, cmd->args);
	else if (cmd->builtin == BD_CD)
		ms_cd(cmd->cmd, cmd->args, env);
	else if (cmd->builtin == BD_EXPORT)
		ms_export(cmd->cmd, &cmd->args[1], env);
	return (EXIT_SUCCESS);
}

int	set_fd(t_cmdlst **cmds)
{
	int			pipes[2];
	t_cmdlst	*tmp;

	if (pipe(pipes) < 0)
		exit(errno);
	if ((*cmds)->cmd->fd_out == -1)
		(*cmds)->cmd->fd_out = pipes[1];
	tmp = (*cmds)->next->next;
	if (tmp->cmd->fd_in == -1)
		tmp->cmd->fd_in = pipes[0];
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

int	exec_cmd(t_cmdlst **cmds, char **env)
{
	t_cmd	*cmd;

	cmd = (*cmds)->cmd;
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(errno);
	if (cmd->builtin == BD_EXIT || cmd->builtin == BD_EXPORT || cmd->builtin == BD_CD)
		ms_builtin(cmd, env);
	if (cmd->pid == 0)
	{
		update_fd(cmd);
		if (cmd->builtin)
			exit(ms_builtin(cmd, env));
		if (execve(cmd->cmd, cmd->args, env) < 0)
			exit(errno);
	}
	else
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		if (cmd->fd_out > 0)
			close(cmd->fd_out);
	}
	return (EXIT_SUCCESS);
}
