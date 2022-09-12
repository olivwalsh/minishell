/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 15:23:10 by owalsh           ###   ########.fr       */
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
		ms_cd(cmd->cmd, cmd->args);
	else if (cmd->builtin == BD_EXPORT)
		ms_export(cmd->cmd, &cmd->args[1], env);
	return (EXIT_SUCCESS);
}

int	ms_wait(t_cmdlst **cmds)
{
	int		error;
	int		exit_status;
	t_cmdlst	*tmp;

	error = 0;
	while ((*cmds)->prev)
		*cmds = (*cmds)->prev;
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->cmd)
		{
			waitpid(tmp->cmd->pid, &exit_status, 0);
			if (WIFEXITED(exit_status))
				error = WEXITSTATUS(exit_status);
			if (error)
			{
				write(2, strerror(error), ft_strlen(strerror(error)));
				write(2, "\n", 1);
				return (error);
			}
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	set_fd(t_cmdlst **cmds)
{
	int	pipes[2];
	t_cmdlst	*tmp;
	
	pipe(pipes);
	(*cmds)->cmd->fd_out = pipes[1];
	tmp = (*cmds)->next->next;
	tmp->cmd->fd_in = pipes[0];
	return (EXIT_SUCCESS);
}

int	ms_execve(t_cmdlst **cmds, char **env)
{
	t_cmd	*cmd;

	cmd = (*cmds)->cmd;
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(errno);
	if (cmd->builtin == BD_EXIT)
		ms_exit(cmd->cmd, &cmd->args[1], env);
	if (cmd->pid == 0)
	{
		if (cmd->fd_in > 0)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out > 0)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
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

int	ms_execute(t_cmdlst **cmds, char **env)
{
	if (!env)
		return (EXIT_FAILURE);
	if ((*cmds)->next && (*cmds)->next->type == PIPE)
		set_fd(cmds);
	if ((*cmds)->type == WORD)
		ms_execve(cmds, env);
	if ((*cmds)->next)
		ms_execute(&(*cmds)->next, env);
	return (EXIT_SUCCESS);
}
