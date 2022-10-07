/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:12:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/07 17:42:47 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int code, char c, int err)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (code == MALLOC_ERR)
		write(STDERR_FILENO, "malloc function failed\n", 24);
	else if (code == SYNTAX_ERR)
	{
		write(STDERR_FILENO, "syntax error near unexpected token `", 36);
		write(STDERR_FILENO, &c, 1);
		write(STDERR_FILENO, "'\n", 3);
	}
	if (err)
		g_global.data->err = 1;
	return (EXIT_FAILURE);
}

char	*err_msg_str(int code)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (code == MALLOC_ERR)
		write(STDERR_FILENO, "malloc function failed\n", 24);
	else if (code == SYNTAX_ERR)
		write(STDERR_FILENO, \
			"syntax error near unexpected token `newline'\n", 46);
	else if (code == MISS_CMD)
		write(STDERR_FILENO, "missing command after redirection\n", 35);
	else if (code == AMB_REDIR)
		write(STDERR_FILENO, "ambiguous redirect\n", 20);
	g_global.data->err = 1;
	return (NULL);
}

int	err_cmd(int code, char *cmd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	if (code == NO_CMD)
	{
		write(STDERR_FILENO, ": command not found\n", 21);
		return (NO_CMD);
	}
	else if (code == NO_FILE)
		write(STDERR_FILENO, ": no such file or directory\n", 29);
	else if (code == FILE_ARG)
		write(STDERR_FILENO, ": filename argument required\n", 30);
	else if (errno)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		return (errno);
	}
	return (EXIT_FAILURE);
}

int	err_bd(int code, int err, char *func, char *arg)
{
	write(STDERR_FILENO, func, ft_strlen(func));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	if (arg && err)
		write(STDERR_FILENO, ": ", 2);
	if (code == NO_FILE)
		write(STDERR_FILENO, ": no such file or directory\n", 29);
	else if (code == NO_OPTION)
		write(STDERR_FILENO, ": invalid option\n", 18);
	else if (code == NO_ID)
		write(STDERR_FILENO, "': not a valid identifier\n", 27);
	else if (code == TOO_MANY_ARGS)
		write(STDERR_FILENO, ": too many arguments\n", 22);
	else if (code == NUM_ARG)
		write(STDERR_FILENO, ": numeric argument required\n", 29);
	if (errno)
	{
		write(STDERR_FILENO, strerror(err), ft_strlen(strerror(err)));
		write(STDERR_FILENO, "\n", 1);
	}
	g_global.data->err = 1;
	return (EXIT_FAILURE);
}
