/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:58 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/07 18:19:31 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char *str)
{
	char	*special;
	char	*operand;
	int		i;

	i = 0;
	special = "|<>\'\"()";
	operand = "&&";
	while (str && str[i] && (str[i] > 32 && str[i] < 127) \
		&& !strchr(special, str[i]) && ft_strncmp(operand, &str[i], 2))
	{
		if (str[i] == '$' && is_delimiter(&str[i + 1]))
			break ;
		i++;
	}
	return (i);
}

int	is_delimiter_spc(char *str)
{
	char	*special;
	char	*operand;
	int		i;

	i = 0;
	special = "|<>\'\"()";
	operand = "&&";
	while (str && str[i] && (str[i] > 31 && str[i] < 127) \
		&& !strchr(special, str[i]) && ft_strncmp(operand, &str[i], 2))
	{
		if (str[i] == '$' && is_delimiter_spc(&str[i + 1]))
			break ;
		else if (str[i] == ' ' && str[i + 1] > 32 && str[i + 1] < 127)
		{
			i++;
			break ;
		}
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

	j = is_delimiter_spc(str);
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
	value = NULL;
	while (str && str[j] && str[j] != str[0])
		j++;
	value = malloc(sizeof(char) * (j + 2));
	if (!value)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	value = ft_strncpy(value, str, j + 1);
	*i += j + 1;
	return (value);
}
