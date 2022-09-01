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

static void	check_new(t_token *new)
{
	t_token	*tmp;

	tmp = new;
	while (tmp)
	{
		if (tmp->value[0] == '$')
			tmp->var_stop = -1;
		tmp = tmp->next;
	}
}

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
		return (EXIT_SUCCESS);
	}
	ms_lexer(str, &new);
	if (!new)
		return (EXIT_FAILURE);
	check_new(new);
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}
