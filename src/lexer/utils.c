/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:19:11 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/23 19:14:34 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_msg(int	code, char c)
{
	if (code == -1)
		printf("minishell: syntax near unexpected token `%c'\n", c);
	else if (code == -2)
		printf("minishell: malloc failed\n");
	
	g_global.data->err = 1;
	return (0);
}

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
	printf("is_quote, str = %s\n", str);
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
	return (err_msg(-1, str[0]));
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

int	is_special(char c, int *type)
{
	if (c == '|')
		*type = PIPE;
	else if (c == '<')
		*type = REDIR_IN;
	else if (c == '>')
		*type = REDIR_OUT;
	else if (c == '$')
		*type = VAR;
	else 
		return (0);
	return (1);
}

void	display_tokens()
{
	t_token	*tmp;

	if (g_global.data->tokens)
	{
		tmp = g_global.data->tokens;
		while (tmp)
		{
			printf(GREEN"token->prev = %p\t\ttoken = %p\t\ttoken->next = %p\n"RESET, tmp->prev, tmp, tmp->next);
			printf(GREEN"token->value = %s\t\ttoken->type = %d\n\n"RESET, tmp->value, tmp->type);
			tmp = tmp->next;
		}
	}
}
