/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/01 16:21:53 by owalsh           ###   ########.fr       */
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

void	delete_token(t_token **tokens)
{
	t_token	*prev;
	t_token	*next;

	prev = (*tokens)->prev;
	next = (*tokens)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free((*tokens)->value);
	free(*tokens);
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
		delete_token(tokens);
		return (EXIT_SUCCESS);
	}
	ms_lexer(str, &new);
	if (!new)
		return (EXIT_FAILURE);
	check_new(new);
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}
