/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:16:38 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/06 14:46:15 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_lexer(char *str, t_token **tokens, int *res)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	if (!str || !str[0])
		return (*res);
	while (str && str[i] && !g_global.data->err)
	{
		while (str[i] && is_isspace(str[i]))
			i++;
		if (str[i] && is_quote(&str[i], &type))
			*res = tokenize(tokens, &str[i], &i, type);
		else if (str[i] && is_oper(str[i], str[i + 1], &type))
			*res = tokenize(tokens, &str[i], &i, type);
		else if (str[i] && is_special(&str[i], &type))
			*res = tokenize(tokens, &str[i], &i, type);
		else if (str[i])
			*res = tokenize(tokens, &str[i], &i, WORD);
	}
	if (g_global.data->err)
		*res = EXIT_FAILURE;
	if (!*res)
		*res = lexer_checker(*tokens);
	return (*res);
}
