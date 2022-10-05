/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:34:44 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/05 17:08:17 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char *str)
{
	char	*special;
	char	*operand;
	int		i;

	i = 0;
	special = "|<>\'\"()$";
	operand = "&&";
	while (str && str[i] && (str[i] > 32 && str[i] < 127) \
		&& !strchr(special, str[i]) && ft_strncmp(operand, &str[i], 2))
		i++;
	return (i);
}

int	is_delimiter_var(char *str)
{
	char	*special;
	char	*operand;
	int		i;

	i = 0;
	special = "|<>\'\"().$";
	operand = "&&";
	while (str && str[i] && (str[i] > 32 && str[i] < 127) \
		&& !strchr(special, str[i]) && ft_strncmp(operand, &str[i], 2))
		i++;
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
