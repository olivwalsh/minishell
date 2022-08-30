/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/29 17:30:45 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var(t_token **tokens, char *var)
{
	if (!var[1] || is_isspace(var[1]))
	{
		(*tokens)->exp = -1;
		return (1);
	}	
	return (0);
}

char	*get_var(t_token **tokens, char *var)
{
	char	*str;
	
	if (check_var(tokens, var))
		return (var);
	var++;
	str = getenv(var++);
	return (str);
}

int	expanse_var(t_token **tokens)
{
	t_token	*new;
	char	*str;

	new = NULL;
	str = get_var(tokens, (*tokens)->value);
	if ((*tokens)->exp == -1)
		return (EXIT_SUCCESS);
	if (!str)
	{
		(*tokens)->value = NULL;
		(*tokens)->type = 0;
		return (EXIT_SUCCESS);
	}
	ms_lexer(str, &new);
	if (!new)
		return (EXIT_FAILURE);
	if (str[0] == '$')
		new->exp = -1;
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}
