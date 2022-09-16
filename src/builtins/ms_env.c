/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/16 14:31:42 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env(char *cmd, char **args, char **env)
{
	if (ft_strcmp("env", cmd))
		return (EXIT_FAILURE);
	if (args && args[0])
		return (err_bd(-1, "env: ", args[0]));
	else
		display_env(env);
	return (EXIT_SUCCESS);
}
