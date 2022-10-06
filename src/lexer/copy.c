/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:58 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/06 11:43:11 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_chars(char *str, int *i, int n)
{
	char	*value;
	int		j;

	value = malloc(sizeof(char) * (n + 1));
	if (!value)
		return (err_msg_str(MALLOC_ERR));
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
		return (err_msg_str(MALLOC_ERR));
	value = ft_strncpy(value, str, j);
	*i += j;
	return (value);
}

char	*copy_var(char *str, int *i)
{
	int		j;
	char	*value;

	j = is_delimiter_var(&str[1]) + 1;
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
		return (err_msg_str(MALLOC_ERR));
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
	while (str && str[j])
	{
		if (str[j] == str[0])
		{
			while (str && str[j + 1] && str[j + 1] == ' ')
				j++;
			break ;
		}
		j++;
	}
	value = malloc(sizeof(char) * (j + 2));
	if (!value)
		return (err_msg_str(MALLOC_ERR));
	value = ft_strncpy(value, str, j + 1);
	*i += j + 1;
	return (value);
}
