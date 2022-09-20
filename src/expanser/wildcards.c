/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:57:07 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/20 14:57:39 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_file(t_token **wildcard, char *file)
{
	if (!ft_strcmp(file, ".") || !ft_strcmp(file, ".."))
		return ;
	file = ft_strjoin(file, " ", 0);
	add_token(create_token(WORD, file), wildcard);
}

int	expanse_wildcard(t_token **wildcard)
{
	struct dirent	*entry;
	DIR				*folder;
	char			*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	folder = opendir(pwd);
	if (folder == NULL)
		exit(errno);
	entry = readdir(folder);
	while (entry)
	{
		insert_file(wildcard, entry->d_name);
		entry = readdir(folder);
	}
	delete_token(wildcard);
	closedir(folder);
	return (EXIT_SUCCESS);
}
