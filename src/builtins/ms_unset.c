/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:23 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/06 15:44:53 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset(char *cmd, char **args)
{
	if (ft_strcmp("unset", cmd))
		return (EXIT_FAILURE);
		
	return(EXIT_SUCCESS);
}