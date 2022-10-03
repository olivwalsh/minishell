/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:57:07 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/02 17:02:45 by owalsh           ###   ########.fr       */
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
	while (wildcard && wildcard[i] && wildcard[i] != '*')
		i++;
	if (i != 0)
		*prefix = ft_strndup(wildcard, i);
	j = i + 1;
	while (wildcard && wildcard[j])
		j++;
	if (j != i + 1)
		*suffix = ft_strndup(&wildcard[i + 1], j);
}

static void	insert_file(t_token **token, char *file)
{
	char	*prefix;
	char	*suffix;
	int		plen;

	plen = 0;
	specify_wildcard((*token)->value, &prefix, &suffix);
	if (prefix)
		plen = ft_strlen(prefix);
	if (!ft_strcmp(file, ".") || !ft_strcmp(file, ".."))
		return ;
	if ((prefix && !suffix && !ft_strncmp(file, prefix, plen))
		|| (suffix && !prefix && has_suffix(file, suffix))
		|| (suffix && prefix
			&& !ft_strncmp(file, prefix, plen) && has_suffix(file, suffix))
		|| (!suffix && !prefix))
	{
		file = ft_strjoin(file, " ", 0);
		add_token(create_token(WORD, file), token);
	}
}

int	expanse_wildcard(t_token **token)
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
		insert_file(token, entry->d_name);
		entry = readdir(folder);
	}
	delete_token(token);
	display_tokens();
	closedir(folder);
	return (EXIT_SUCCESS);
}
