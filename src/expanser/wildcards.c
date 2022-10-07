/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:57:07 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/07 13:04:38 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_file(t_token **token, char *file, int *found)
{
	file = ft_strjoin(file, " ", 0);
	add_token(create_token(WORD, file), token);
	*found = TRUE;
}

static int	next_wc(char *wildcard)
{
	int	i;

	i = 0;
	while (wildcard && wildcard[i] && wildcard[i] != '*')
		i++;
	if (i == ft_strlen(wildcard))
		return (-1);
	return (i);
}

static int	check_file(char *wildcard, char *file)
{
	int		wc;
	int		i;

	i = 0;
	wc = next_wc(wildcard);
	if (wildcard && wildcard[0] == '*' && wildcard[1])
	{
		while (file && file[i])
		{
			if (file[i] == wildcard[1])
				return (check_file(&wildcard[1], &file[i]));
			i++;
		}
		if (i == ft_strlen(file))
			return (EXIT_FAILURE);
	}
	else if (wildcard && wildcard[0] == '*' && !wildcard[1])
		return (EXIT_SUCCESS);
	else if (wc != -1 && !ft_strncmp(file, wildcard, wc))
		return (check_file(wildcard + wc, file + wc));
	else if (wc == -1 && !ft_strncmp(file, wildcard, ft_strlen(wildcard) + 1))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int	err_getcwd(char *pwd)
{
	free(pwd);
	return (EXIT_FAILURE);
}

int	expanse_wildcard(t_token **token)
{
	struct dirent	*entry;
	DIR				*folder;
	char			*pwd;
	int				found;

	found = FALSE;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (err_getcwd(pwd));
	folder = opendir(pwd);
	if (folder == NULL)
		exit(errno);
	entry = readdir(folder);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, "..", 3)
			&& ft_strncmp(entry->d_name, ".", 2)
			&& !check_file((*token)->value, entry->d_name))
			insert_file(token, entry->d_name, &found);
		entry = readdir(folder);
	}
	if (found)
		delete_token(token);
	closedir(folder);
	free(pwd);
	return (EXIT_SUCCESS);
}
