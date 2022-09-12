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

// int	ms_dupwrite(t_cmdlst **cmds, t_cmd *cmd, int pipe_out)
// {
// 	(void)cmds;
// 	// cmd > outfile
// 	if (cmd->redir)
// 	{
// 		if (cmd->redir->redir_out || cmd->redir->append_out)
// 			return (dup2(cmd->fd_out, STDOUT_FILENO)); // this is working
// 	}
// 	// cmd | cmd > outfile
// 	// cmd > outfile | cmd
	
// 	return (dup2(cmd->fd_out, STDOUT_FILENO))
// 	// cmd
	
	
// 	// cmd | cmd
// 	// else if ((*cmds)->next->type == PIPE)
// 	// 	return (dup2(pipe_out, STDOUT_FILENO));
	
	
// 	// if no redir to outfile, write to stdout but read from pipe in (other cmd before)
// 	else
// 		return (dup2(STDOUT_FILENO, pipe_out));
// 	return (EXIT_SUCCESS);
// }

// int	ms_dupread(t_cmdlst **cmds, t_cmd *cmd, int pipe_in)
// {
// 	(void)cmds;
// 	if (cmd->redir)
// 	{
// 		if (cmd->redir->redir_in || cmd->redir->append_in)
// 			return (dup2(cmd->fd_in, STDIN_FILENO)); // this is working
// 	}
// 	else
// 		return (dup2(pipe_in, STDIN_FILENO));
// 	return (EXIT_SUCCESS);
// }

// int	ms_execve(t_cmdlst **cmds, char **env)
// {
// 	pid_t	pid;
// 	int		pipes[2];
// 	t_cmd	*cmd;

// 	cmd = (*cmds)->cmd;
// 	pipe(pipes);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(errno);
// 	if (cmd->builtin == BD_EXIT)
// 		ms_exit(cmd->cmd, &cmd->args[1], env);
// 	if (pid == 0)
// 	{
// 		if (ms_dupread(cmds, cmd, pipes[0]) < 0)
// 			exit(errno);
// 		if (ms_dupwrite(cmds, cmd, pipes[1]) < 0)
// 			exit(errno);
// 		if (cmd->builtin)
// 			exit(ms_builtin(cmd, env));
// 		if (execve(cmd->cmd, cmd->args, env) < 0)
// 			exit(errno);
// 	}
// 	return (ms_wait(pid));
// }

// int	ms_setfd(t_cmdlst **cmds)
// {
// 	if (!(*cmds))
// 		return (EXIT_FAILURE);
// 	if ((*cmds)->type == PIPE)
// 		ms_setfd((*cmds)->next);
// 	pipe((*cmds)->cmd->pipe);
// 	ms_setfd((*cmds)->next);
// 	return (EXIT_SUCCESS);
// }

int	set_fd(t_cmdlst **cmds)
{
	int	pipes[2];
	t_cmdlst	*tmp;
	
	pipe(pipes);
	(*cmds)->cmd->fd_out = pipes[1];
	printf("in set_fd, cmd->fd_out is %d\n", (*cmds)->cmd->fd_out);
	tmp = (*cmds)->next->next;
	tmp->cmd->fd_in = pipes[0];
	printf("in set_fd, cmd->fd_in is %d\n", tmp->cmd->fd_in);
	return (EXIT_SUCCESS);
}

int	ms_execve(t_cmdlst **cmds, char **env)
{
	pid_t	pid;
	t_cmd	*cmd;

	cmd = (*cmds)->cmd;
	pid = fork();
	if (pid == -1)
		exit(errno);
	if (cmd->builtin == BD_EXIT)
		ms_exit(cmd->cmd, &cmd->args[1], env);
	if (pid == 0)
	{
		printf("cmd->fd_in is %d\n", cmd->fd_in);
		if (cmd->fd_in > 0)
			dup2(cmd->fd_in, STDIN_FILENO);
		printf("cmd->fd_out is %d\n", cmd->fd_out);
		if (cmd->fd_out > 0)
			dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_in);
		close(cmd->fd_out);
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
	if ((*cmds)->next->type == PIPE)
		set_fd(cmds);
	if ((*cmds)->type == PIPE)
		*cmds = (*cmds)->next;
	else if ((*cmds)->type == WORD)
		ms_execve(cmds, env);
	if ((*cmds)->next)
		ms_execute(&(*cmds)->next, env);
	return (EXIT_SUCCESS);
}
