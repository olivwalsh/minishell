/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:01:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 13:43:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(int err, char *path)
{
	write(2, "cd: ", 4);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}
