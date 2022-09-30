/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:33:00 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 17:53:38 by owalsh           ###   ########.fr       */
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

void	sig_eof(char *delimiter)
{
	write(2, "minishell: ", 11);
	write(2, "warning: here-document delimited by end-of-file (wanted `", 57);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
}

int	read_stdin(char *delimiter, int fd)
{
	char	*line;

	write(1, "> ", 2);
	line = get_next_line(0);
	if (!line)
		sig_eof(delimiter);
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter)))
	{
		write(fd, line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			sig_eof(delimiter);
	}
	free(line);
	close(fd);
	return (EXIT_SUCCESS);
}

int	fork_stdin(char *delimiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (EXIT_FAILURE);
	g_global.data->shell.fd_heredoc[0] = fd[0];
	g_global.data->shell.heredoc = 1;
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	g_global.data->shell.pid_heredoc = pid;
	if (pid == 0)
	{
		read_stdin(delimiter, fd[1]);
		exit(0);
	}
	wait(NULL);
	close(fd[1]);
	g_global.data->shell.heredoc = 0;
	return (fd[0]);
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
