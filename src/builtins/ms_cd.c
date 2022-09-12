/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:29:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/09 13:54:14 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error(int err)
{
	write(2, "minishell: ", 11);
	if (err == -10)
		write(2, "missing arguments.", 18);
	else if (err == -11)
		write(2, "too many arguments in function call.", 36);
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}

// int	ms_export_cheat(char *var, char *value)
// {
// 	pid_t	pid;
// 	int		pipes[2];
// 	char	*str;
	
// 	str = NULL;
// 	str = ft_strjoin(str, "export ", 1);
// 	str = ft_strjoin(str, var, 1);
// 	str = ft_strjoin(str, "=", 1);
// 	str = ft_strjoin(str, value, 1);
// 	pipe(pipes);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(errno);
// 	if (pid == 0)
// 	{
// 		dup2(pipes[0], STDIN_FILENO);
// 		dup2(STDOUT_FILENO, pipes[1]);
// 		if (execve("export", ft_split(str, ' '), g_global.data->shell.env) < 0)
// 			exit(errno);
// 	}
// 	return (ms_wait(pid));
// }

int	set_workingdirectory(char *path)
{
	// char	*newpath;
	char	*oldpath;

	printf("in set working directory with new path = %s\n", path);
	oldpath = getenv("PWD");
	printf("pwd path is: %s\n", oldpath);
	// ms_export_cheat("OLDPWD", oldpath);
	// ms_export_cheat("PWD", path);
	return (EXIT_SUCCESS);
}

int	ms_cd(char *cmd, char **args)
{
	if (ft_strcmp(cmd, "cd"))
		return (EXIT_FAILURE);
	if (!args[1])
		return (exec_error(-10));
	if (args[2])
		return (exec_error(-11));
	set_workingdirectory(args[1]);
	return (EXIT_SUCCESS);
}
