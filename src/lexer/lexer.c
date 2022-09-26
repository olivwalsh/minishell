/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:16:38 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/26 15:45:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_lexer(char *str, t_token **tokens)
{
	int	i;
	int	res;
	int	type;

	i = 0;
	res = 0;
	type = 0;
	while (str && str[i] && !g_global.data->err)
	{
		while (str[i] && is_isspace(str[i]))
			i++;
		if (str[i] && is_quote(&str[i], &type))
			res = tokenize(tokens, &str[i], &i, type);
		else if (str[i] && is_oper(str[i], str[i + 1], &type))
			res = tokenize(tokens, &str[i], &i, type);
		else if (str[i] && is_special(&str[i], &type))
			res = tokenize(tokens, &str[i], &i, type);
		else if (str[i])
			res = tokenize(tokens, &str[i], &i, WORD);
	}
	if (g_global.data->err || !str || !str[0])
		return (EXIT_FAILURE);
	res = lexer_checker(*tokens);
	return (res);
}
