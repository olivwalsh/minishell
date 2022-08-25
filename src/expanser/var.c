/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/24 15:21:00 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanse_var(t_token **tokens)
{
	t_token	*new;
	char	*str;
	char	*var;

	new = NULL;
	var = (*tokens)->value;
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
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}
