/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:14:01 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/19 16:15:29 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_init(t_data *data, char **argv, char **env)
{
	(void)argv;
	memset(data, 0, sizeof(t_data));
	g_global.data = data;
	if (copy_env(data, env))
		return (EXIT_FAILURE);
	init_terminal();
	return (EXIT_SUCCESS);
}
