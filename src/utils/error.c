/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:12:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/15 12:00:41 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int code, char c)
{
	if (code == -1)
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	else if (code == -2)
		printf("minishell: malloc failed\n");
	g_global.data->err = 1;
	return (EXIT_FAILURE);
}

int	err_msg_1(int code, char c)
{
	if (code == -1)
		printf("minishell: syntax error near unexpected token `%c'\n", c);
	else if (code == -2)
		printf("minishell: malloc failed\n");
	return (EXIT_FAILURE);
}

char	*err_msg_str(int code, char *str)
{
	if (!str)
		str = "newline";
	if (code == -1)
		printf("minishell: syntax error near unexpected token `%s'\n", str);
	else if (code == -2)
		printf("minishell: malloc failed\n");
	else if (code == -3)
		printf("minishell: %s\n", str);
	g_global.data->err = 1;
	return (NULL);
}

int	err_bd(int code, char *func, char *arg)
{
	char	*str;

	str = NULL;
	str = ft_strjoin(str, func, 1);
	str = ft_strjoin(str, arg, 1);
	if (code == -1)
		str = ft_strjoin(str, ": No such file or directory\n", 1);
	else if (code == -2)
		str = ft_strjoin(str, ": Invalid option\n", 1);
	else if (code == -3)
		str = ft_strjoin(str, "': not a valid identifier\n", 1);
	write(STDERR_FILENO, str, ft_strlen(str));
	free(str);
	return (EXIT_FAILURE);
}

int	err_cmd(char *cmd)
{
	char	*str;

	str = NULL;
	str = ft_strjoin(str, "minishell: ", 1);
	str = ft_strjoin(str, cmd, 1);
	str = ft_strjoin(str, ": command not found\n", 1);
	write(STDERR_FILENO, str, ft_strlen(str));
	free(str);
	return (EXIT_FAILURE);
}

// int error(t_token token, int code)
