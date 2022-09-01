/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:12:41 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/28 20:49:39 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int code, char c)
{
	if (code == -1)
		printf("minishell: syntax near unexpected token `%c'\n", c);
	else if (code == -2)
		printf("minishell: malloc failed\n");
	g_global.data->err = 1;
	return (EXIT_FAILURE);
}

// int error(t_token token, int code)
