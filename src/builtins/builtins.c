/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:56:16 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 18:41:57 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_buildin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 5))
		return (BD_ECHO);
	else if (!ft_strncmp("cd", cmd, 3))
		return (BD_EXIT);
	else if (!ft_strncmp("pwd", cmd, 4))
		return (BD_EXIT);
	else if (!ft_strncmp("export", cmd, 7))
		return (BD_EXPORT);
	else if (!ft_strncmp("unset", cmd, 6))
		return (BD_UNSET);
	else if (!ft_strncmp("env", cmd, 4))
		return (BD_ENV);
	else if (!ft_strncmp("exit", cmd, 5))
		return (BD_EXIT);
	else
		return (EXIT_FAILURE);
}
