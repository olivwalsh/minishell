/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:18:06 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 18:54:08 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_lines(char *s, char c)
{
	int	i;
	int	words;

	i = 1;
	words = 0;
	if (s[0] != c)
		words++;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			words++;
		i++;
	}
	return (words);
}

char	**free_previous(char **str, int x)
{
	while (x <= 0)
		free(str[x--]);
	free(str);
	return (NULL);
}

void	fill(char *str, char **split, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		(*split)[i] = str[i];
		i++;
	}
	(*split)[i] = '\0';
}

static char	**linemalloc(char **split, char *s, char c)
{
	int	i;
	int	x;

	x = 0;
	while (*s)
	{
		i = 0;
		if (*s && s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			split[x] = malloc(sizeof(char) * (i + 1));
			if (!split[x])
				return (free_previous(split, x));
			fill(s, &split[x], c);
			x++;
			s += i;
		}
		else
			s++;
	}
	return (split);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		words;

	if (!s)
		return (NULL);
	if (*s == 0)
		words = 0;
	else
		words = count_lines(s, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	if (!linemalloc(split, s, c))
		return (NULL);
	split[words] = NULL;
	return (split);
}
