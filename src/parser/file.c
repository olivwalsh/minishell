/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:33:00 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 13:56:42 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		return (0);
	}
	return (fd);
}

int	read_stdin(char *delimiter)
{
	char	*line;
	int		newfile;

	newfile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (newfile == -1)
		return (0);
	line = get_next_line(0);
	while (ft_strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		write(newfile, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	return (read_file("tmp"));
}

int	create_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (0);
	return (fd);
}

int	append_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (0);
	return (fd);
}
