/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:01:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/13 17:43:23 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(int err, char *path)
{
	write(2, "minishell: ", 11);
	if (err == -11)
		write(2, "too many arguments in function call.", 36);
	else if (err == ENOENT)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory", 28);
	}
	else if (err == ENOTDIR)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": Not a directory", 17);
	}
	else if (err == EACCES)
	{
		write(2, "cd: ", 4);
		write(2, path, ft_strlen(path));
		write(2, ": Permission denied", 19);
	}
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}
