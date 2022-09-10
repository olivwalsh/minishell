/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/09 16:59:50 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin(t_cmdlst **cmds, char **env)
{
	if ((*cmds)->cmd->builtin == BD_EXIT)
		ms_exit((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
	else if ((*cmds)->cmd->builtin == BD_ENV)
		ms_env((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
	else if ((*cmds)->cmd->builtin == BD_EXPORT)
		ms_export((*cmds)->cmd->cmd, &(*cmds)->cmd->args[1], env);
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
	waitpid(pid, NULL, 0);
	return (EXIT_SUCCESS);
}

int	ms_execute(t_cmdlst **cmds, char **env)
{
	if ((*cmds)->cmd->builtin)
		ms_builtin(cmds, env);
	else
		ms_execve(cmds, env);
	return (EXIT_SUCCESS);
}
