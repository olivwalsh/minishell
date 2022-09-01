/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:11 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/29 15:18:21 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	is_quote(char *str, int *type)
{
	int	i;

	i = 0;
	if (str[0] != DQUOTE && str[0] != SQUOTE)
		return (0);
	i++;
	while (str && str[i])
	{
		if (str[i] == str[0])
		{
			if (str[i] == 34)
				*type = DBL_QUOTE;
			else if (str[i] == 39)
				*type = SGL_QUOTE;
			return (1);
		}
		i++;
	}
	err_msg(-1, str[0]);
	return (0);
}

int	is_oper(char c1, char c2, int *type)
{
	if (c1 != c2)
		return (0);
	if (c1 == '&')
		*type = OPERAND;
	else if (c1 == '|')
		*type = OPEROR;
	else if (c1 == '<')
		*type = APPEND_IN;
	else if (c1 == '>')
		*type = APPEND_OUT;
	else
		return (0);
	return (1);
}

int	is_var(char *str)
{
	char	*special;

	special = "|<>\'\"&()";
	if (str && str[0] == '$')
	{
		if ((str[1] > 32 && str[1] < 127) && !is_isspace(str[1])
			&& !strchr(special, str[1]))
			return (1);
	}
	return (0);
}

int	is_special(char *str, int *type)
{
	char	c;

	c = str[0];
	if (c == '|')
		*type = PIPE;
	else if (c == '<')
		*type = REDIR_IN;
	else if (c == '>')
		*type = REDIR_OUT;
	else if (is_var(str))
		*type = VAR;
	else if (c == '(')
		*type = OPEN_BRK;
	else if (c == ')')
		*type = CLOSE_BRK;
	else
		return (0);
	return (1);
}
