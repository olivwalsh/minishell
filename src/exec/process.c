/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:47:30 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/05 12:04:30 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_parent(t_cmd *cmd, char **env)
{
	int	res;

	res = EXIT_SUCCESS;
	if (cmd->builtin == BD_EXIT)
		res = ms_exit(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_CD)
		res = ms_cd(cmd->cmd, cmd->args, env);
	else if (cmd->builtin == BD_EXPORT)
		res = ms_export(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_UNSET)
		res = ms_unset(cmd->cmd, &cmd->args[1], env);
	return (res);
}

int	ms_builtin_child(t_cmd *cmd, char **env)
{
	if (cmd->builtin == BD_ENV)
		ms_env(cmd->cmd, &cmd->args[1], env);
	else if (cmd->builtin == BD_ECHO)
		ms_echo(cmd->cmd, cmd->args);
	else if (cmd->builtin == BD_PWD)
		exit(ms_pwd(cmd->cmd, cmd->args, env));
	else if (cmd->builtin == BD_EXPORT)
		exit(EXIT_SUCCESS);
	else if (cmd->builtin == BD_UNSET)
		exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	exec_cmd(t_cmdlst **cmds, char **env)
{
	t_cmd	*cmd;
	int		res;

	res = EXIT_SUCCESS;
	cmd = (*cmds)->cmd;
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(errno);
	if (cmd->pid == 0)
	{
		if (!cmd->cmd && !cmd->redir)
			exit(127);
		if (!cmd->cmd)
			exit(0);
		update_fd(cmd);
		if (cmd->builtin)
			exit(ms_builtin_child(cmd, env));
		if (execve(cmd->cmd, cmd->args, env) < 0)
			exit(errno);
	}
	else
	{
		if (cmd->builtin == BD_EXIT || cmd->builtin == BD_EXPORT || \
			cmd->builtin == BD_CD || cmd->builtin == BD_UNSET)
			res = ms_builtin_parent(cmd, env);
		close_fd(cmd);
	}
	return (res);
}
