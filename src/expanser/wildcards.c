/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:57:07 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 15:09:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_file(t_token **token, char *file, int *found)
{
	t_token	*new;
	t_token	*next;

	next = (*token)->next;
	file = ft_strjoin(file, " ", 0);
	new = create_token(WORD, file, 1);
	(*token)->next = new;
	new->prev = *token;
	new->next = next;
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

static void	read_directory(char *pwd, t_token **token, char *wildcard)
{
	struct dirent	*entry;
	DIR				*folder;
	int				found;

	found = FALSE;
	folder = opendir(pwd);
	if (folder == NULL)
		exit(errno);
	entry = readdir(folder);
	while (entry)
	{
		if (ft_strncmp(entry->d_name, "..", 3)
			&& ft_strncmp(entry->d_name, ".", 2)
			&& !check_file(wildcard, entry->d_name))
			insert_file(token, entry->d_name, &found);
		entry = readdir(folder);
	}
	if (found)
		delete_token(token);
	closedir(folder);
}

int	expanse_wildcard(t_token **token)
{
	char			*pwd;
	char			*wildcard;

	wildcard = (*token)->value;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		free(pwd);
		return (EXIT_FAILURE);
	}
	read_directory(pwd, token, wildcard);
	free(pwd);
	return (EXIT_SUCCESS);
}
