/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:57:07 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 19:06:27 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_suffix(char *file, char *suffix)
{
	int	slen;
	int	flen;

	slen = ft_strlen(suffix) - 1;
	flen = ft_strlen(file) - 1;
	while (slen >= 0)
	{
		if (file[flen] != suffix[slen])
			return (0);
		slen--;
		flen--;
	}
	return (1);
}

static void	specify_wildcard(char *wildcard, char **prefix, char **suffix)
{
	int		i;
	int		j;

	i = 0;
	*prefix = NULL;
	*suffix = NULL;
	
		*prefix = ft_strndup(wildcard, i);
	j = i + 1;
	while (wildcard && wildcard[j])
		j++;
	if (j != i + 1)
		*suffix = ft_strndup(&wildcard[i + 1], j);
}

static void	insert_file(t_token **token, char *file, int *found)
{
	file = ft_strjoin(file, " ", 0);
	add_token(create_token(WORD, file), token);
	*found = TRUE;
}

int	next_wc(char *wildcard)
{
	int	i;

	i = 0;
	while (wildcard && wildcard[i] && wildcard[i] != '*')
		i++;
	if (i == 0 || i = ft_strlen(wildcard))
		return (0);
	return (i);
}

static int	check_file(char *wildcard, char *file)
{
	char	*prefix;
	int		wc;
	// char	*suffix;
	// int		plen;

	// plen = 0;
	// specify_wildcard((*token)->value, &prefix, &suffix);
	// if (prefix)
	// 	plen = ft_strlen(prefix);
	if (!ft_strncmp(file, ".", 2) || !ft_strncmp(file, "..", 3))
		return (0);
	wc = next_wc(wildcard);
	while (file && )
	if (!ft_strncmp(file, wildcard, next_wc(wildcard) - 1));
	{
		wildcard += wc;
		file += wc;
	}
	// if ((prefix && !suffix && !ft_strncmp(file, prefix, plen))
	// 	|| (suffix && !prefix && has_suffix(file, suffix))
	// 	|| (suffix && prefix
	// 		&& !ft_strncmp(file, prefix, plen) && has_suffix(file, suffix))
	// 	|| (!suffix && !prefix))
	

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
		if (check_file((*token)->value, entry->d_name))
			insert_file(token, entry->d_name, &found);
		entry = readdir(folder);
	}
	if (found)
		delete_token(token);
	closedir(folder);
	return (EXIT_SUCCESS);
}
