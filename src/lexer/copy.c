/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:58 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/25 15:05:08 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char *str)
{
	char	*special;
	int		i;

	i = 0;
	special = "|<>\'\"&()";
	while (str && str[i] && (str[i] > 32 && str[i] < 127) \
		&& !strchr(special, str[i]))
		i++;
	return (i);
}

char	*copy_chars(char *str, int *i, int n)
{
	char	*value;
	int		j;

	value = malloc(sizeof(char) * (n + 1));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	j = 0;
	while (j < n)
	{
		value[j] = str[j];
		j++;
	}
	value[j] = '\0';
	*i += j;
	return (value);
}

char	*copy_word(char *str, int *i)
{
	int		j;
	char	*value;

	j = is_delimiter(str);
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	value = ft_strncpy(value, str, j);
	printf("j = %d \n", j);
	*i += j;
	return (value);
}

char	*copy_quote(char *str, int *i)
{
	char	*value;
	int		j;

	j = 1;
	while (str && str[j] && str[j] != str[0])
		j++;
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	value = ft_strncpy(value, str, j + 1);
	*i += j + 1;
	return (value);
}
