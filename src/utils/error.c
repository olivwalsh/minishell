/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:12:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/04 17:57:30 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int code, char *c, int err)
{
	char	*str;

	str = NULL;
	str = ft_strjoin(str, "minishell: ", 1);
	if (code == -1)
	{
		str = ft_strjoin(str, "syntax error near unexpected token `", 1);
		str = ft_strjoin(str, c, 1);
		str = ft_strjoin(str, "'\n", 1);
	}
	else if (code == -2)
		str = ft_strjoin(str, "malloc function failed\n", 1);
	write(STDERR_FILENO, str, ft_strlen(str));
	free(str);
	if (err)
		g_global.data->err = 1;
	return (EXIT_FAILURE);
}

char	*err_msg_str(int code, char *tmp)
{
	char	*str;

	if (!tmp)
		tmp = "newline";
	str = NULL;
	str = ft_strjoin(str, "minishell: ", 1);
	if (code == -1)
	{
		str = ft_strjoin(str, "syntax error near unexpected token `", 1);
		str = ft_strjoin(str, tmp, 1);
		str = ft_strjoin(str, "'\n", 1);
	}
	else if (code == -2)
		str = ft_strjoin(str, "malloc function failed\n", 1);
	else if (code == -3)
		str = ft_strjoin(str, "missing command after redirection\n", 1);
	write(STDERR_FILENO, str, ft_strlen(str));
	free(str);
	g_global.data->err = 1;
	return (NULL);
}

int	err_bd(int code, int err, char *func, char *arg)
{
	write(STDERR_FILENO, func, ft_strlen(func));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	if (arg && err)
		write(STDERR_FILENO, ": ", 2);
	if (code == -1)
		write(STDERR_FILENO, ": No such file or directory\n", 29);
	else if (code == -2)
		write(STDERR_FILENO, ": Invalid option\n", 18);
	else if (code == -3)
		write(STDERR_FILENO, "': not a valid identifier\n", 27);
	else if (code == -4)
		write(STDERR_FILENO, ": too many arguments\n", 22);
	else if (code == -5)
		write(STDERR_FILENO, ": numeric arguments required\n", 30);
	if (errno)
	{
		write(STDERR_FILENO, strerror(err), ft_strlen(strerror(err)));
		write(STDERR_FILENO, "\n", 1);
	}
	return (EXIT_FAILURE);
}

int	err_cmd(char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": command not found\n", 21);
	return (127);
}
