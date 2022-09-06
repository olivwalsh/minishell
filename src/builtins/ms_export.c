/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:19 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/06 15:44:35 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_export(char *cmd, char **args)
{
	if (ft_strcmp("export", cmd))
		return (EXIT_FAILURE);
		
	return(EXIT_SUCCESS);
}