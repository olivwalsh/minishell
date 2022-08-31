/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:18:24 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/28 16:34:58 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token *new, t_token **tokens)
{
	t_token	*tmp;

	if (*tokens)
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*tokens = new;
}

static t_token	*create_token(int type, char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	new->type = type;
	new->value = value;
	new->var = 0;
	new->qts = NULL;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	tokenize(t_token **tokens, char *str, int *i, int type)
{
	if (type > 1 && type < 7)
		add_token(create_token(type, copy_chars(str, i, 1)), tokens);
	else if (type > 9 && type < 14)
		add_token(create_token(type, copy_chars(str, i, 2)), tokens);
	else if (type == WORD)
		add_token(create_token(type, copy_word(str, i)), tokens);
	else if (type == VAR)
		add_token(create_token(type, copy_var(str, i)), tokens);
	else if (type == SGL_QUOTE || type == DBL_QUOTE)
		add_token(create_token(type, copy_quote(str, i)), tokens);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
