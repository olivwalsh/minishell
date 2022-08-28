/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/28 20:14:24 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var(t_token **tokens, char *var)
{
	if (!var[1] || is_isspace(var[1]))
	{
		(*tokens)->exp = 2;
		return (1);
	}	
	return (0);
}

int	expanse_var(t_token **tokens)
{
	t_token	*new;
	char	*str;
	char	*var;

	new = NULL;
	(*tokens)->exp = 1;
	var = (*tokens)->value;
	if (check_var(tokens, var))
		return (EXIT_SUCCESS);
	var++;
	str = getenv(var++);
	if (!str)
	{
		(*tokens)->value = NULL;
		(*tokens)->type = 0;
	}
	ms_lexer(str, &new);
	if (!new)
		return (EXIT_FAILURE);
	if (str[0] == '$')
		new->exp = 2;
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}
