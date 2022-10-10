/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:33:00 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 19:05:54 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		g_global.data->err = EXIT_FAILURE;
		write(STDERR_FILENO, "minishell: ", 11);
		perror(file);
		// return (0);
	}
	return (fd);
}

int	create_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		g_global.data->err = EXIT_FAILURE;
		write(STDERR_FILENO, "minishell: ", 11);
		perror(file);
		// return (0);
	}
	return (fd);
}

int	append_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		g_global.data->err = EXIT_FAILURE;
		write(STDERR_FILENO, "minishell: ", 11);
		perror(file);
		// return (0);
	}
	return (fd);
}
