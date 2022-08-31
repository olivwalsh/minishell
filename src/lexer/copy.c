/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:58 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/29 15:20:10 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char *str)
{
	char	*special;
	int		i;

	i = 0;
	special = "|<>\'\"&()";
	while (str && str[i] && (str[i] > 32 && str[i] < 127) \
		&& !strchr(special, str[i]))
	{
		if (str[i] == '$' && is_delimiter(&str[i + 1]))
			break ;
		i++;
	}
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
	// printf ("str before delimiter is %s\n", str);
	j = is_delimiter(str);
	// printf ("str after delimiter is %s\n", str);
	value = malloc(sizeof(char) * (j + 1));
	// printf ("str after malloc is %s\n", str);
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	// printf ("str before strncpy is %s\n", str);
	value = ft_strncpy(value, str, j);
	// printf ("value after strncpy is %s\n", value);
	*i += j;
	return (value);
}

char	*copy_var(char *str, int *i)
{
	int		j;
	char	*value;

	j = is_delimiter(&str[1]) + 1;
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	value = ft_strncpy(value, str, j);
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
