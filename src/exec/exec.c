/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 13:52:48 by owalsh           ###   ########.fr       */
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

int	ms_wait(pid_t pid)
{
	int		error;
	int		exit_status;

	error = 0;
	waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
		error = WEXITSTATUS(exit_status);
	if (error)
	{
		write(2, strerror(error), ft_strlen(strerror(error)));
		write(2, "\n", 1);
		return (error);
	}
	return (EXIT_SUCCESS);
}

int	ms_dupwrite(t_cmd *cmd, int pipe_out)
{
	if (cmd->redir)
	{
		if (cmd->redir->redir_out || cmd->redir->append_out)
			return (dup2(cmd->fd_out, STDOUT_FILENO));
	}
	else
		return (dup2(STDOUT_FILENO, pipe_out));
	return (EXIT_SUCCESS);
}

int	ms_dupread(t_cmd *cmd, int pipe_in)
{
	if (cmd->redir)
	{
		if (cmd->redir->redir_in || cmd->redir->append_in)
			return (dup2(cmd->fd_in, STDIN_FILENO));
	}
	else
		return (dup2(pipe_in, STDIN_FILENO));
	return (EXIT_SUCCESS);
}

int	ms_execve(t_cmd *cmd, char **env)
{
	pid_t	pid;
	int		pipes[2];

	pipe(pipes);
	pid = fork();
	if (pid == -1)
		exit(errno);
	if (cmd->builtin == BD_EXIT)
		ms_exit(cmd->cmd, &cmd->args[1], env);
	if (pid == 0)
	{
		if (ms_dupread(cmd, pipes[0]) < 0)
			exit(errno);
		if (ms_dupwrite(cmd, pipes[1]) < 0)
			exit(errno);
		if (cmd->builtin)
			exit(ms_builtin(cmd, env));
		if (execve(cmd->cmd, cmd->args, env) < 0)
			exit(errno);
	}
	return (ms_wait(pid));
}

int	ms_execute(t_cmdlst **cmds, char **env)
{
	if (!env)
		return (EXIT_FAILURE);
	if ((*cmds)->type == PIPE)
		*cmds = (*cmds)->next;
	else if ((*cmds)->type == WORD)
		ms_execve((*cmds)->cmd, env);
	return (EXIT_SUCCESS);
}
