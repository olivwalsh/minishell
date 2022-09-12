/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:29:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 20:01:39 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*

cd
cd ..
cd ~
cd relative/path
cd /absolute/path
cd ./this/is/a/path
cd ~/from/home/dir

-- ERROR -- 
cd ~ziggy

*/



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

int	set_workingdirectory(char **path, char **env)
{
	// char	*newpath;
	char	*oldpath;

	oldpath = getenv("PWD");
	printf("pwd path is: %s\n", oldpath);
	ms_export("export", path, env);
	
	return (EXIT_SUCCESS);
}

int	ms_cd(char *cmd, char **args, char **env)
{
	char	*cwd;
	
	cwd = NULL;
	if (ft_strcmp(cmd, "cd"))
		return (EXIT_FAILURE);
	if (!args[1])
		return (exec_error(-10));
	if (args[2])
		return (exec_error(-11));
	cwd = getcwd(cwd, 0);
	printf("current working directory is %s\n", cwd);
	set_workingdirectory(&args[1], env);
	return (EXIT_SUCCESS);
}
