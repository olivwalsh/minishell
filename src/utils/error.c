/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:12:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/05 14:16:27 by owalsh           ###   ########.fr       */
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

char	*err_msg_str(int code, char *str)
{
	if (!str)
		str = "newline";
	if (code == -1)
		printf("minishell: syntax error near unexpected token `%s'\n", str);
	else if (code == -2)
		printf("minishell: malloc failed\n");
	g_global.data->err = 1;
	return (NULL);
}

// int error(t_token token, int code)
