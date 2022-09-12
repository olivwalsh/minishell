/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 11:27:34 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin(t_cmdlst **cmds, char **env)
{
	if ((*cmds)->cmd->builtin == BD_EXIT)
		ms_exit((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
	else if ((*cmds)->cmd->builtin == BD_ENV)
		ms_env((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
	else if ((*cmds)->cmd->builtin == BD_ECHO)
		ms_echo((*cmds)->cmd->cmd, (*cmds)->cmd->args);
	else if ((*cmds)->cmd->builtin == BD_CD)
		ms_cd((*cmds)->cmd->cmd, (*cmds)->cmd->args);
	else if ((*cmds)->cmd->builtin == BD_EXPORT)
		ms_export((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
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

int	ms_execve(t_cmdlst **cmds, char **env)
{
	pid_t	pid;
	int		pipes[2];

	pipe(pipes);
	pid = fork();
	if (pid == -1)
		exit(errno);
	if (pid == 0)
	{
		dup2(pipes[0], STDIN_FILENO);
		dup2(STDOUT_FILENO, pipes[1]);
		if (execve((*cmds)->cmd->cmd, (*cmds)->cmd->args, env) < 0)
			exit(errno);
	}
	return (ms_wait(pid));
}

int	ms_execute(t_cmdlst **cmds, char **env)
{
	if (!env)
		return (EXIT_FAILURE);
	if ((*cmds)->cmd->builtin)
		return (ms_builtin(cmds, env));
	else
		return (ms_execve(cmds, env));
	return (EXIT_SUCCESS);
}
