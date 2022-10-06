/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:18:24 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/06 16:53:42 by foctavia         ###   ########.fr       */
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

t_token	*create_token(int type, char *value, int spc)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		err_msg_str(MALLOC_ERR);
		return (NULL);
	}
	new->type = type;
	new->value = value;
	new->spc = spc;
	new->var_stop = 0;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

int	tokenize(t_token **tokens, char *str, int *i, int type)
{
	int	spc;

	spc = 0;
	if (type > 1 && type < 7)
		add_token(create_token(type, copy_chars(str, i, 1), spc), tokens);
	else if (type > 9 && type < 14)
		add_token(create_token(type, copy_chars(str, i, 2), spc), tokens);
	else if (type == WORD)
		add_token(create_token(type, copy_word(str, i), spc), tokens);
	else if (type == VAR)
		add_token(create_token(type, copy_var(str, i, &spc), spc), tokens);
	else if (type == SGL_QUOTE || type == DBL_QUOTE)
		add_token(create_token(type, copy_quote(str, i), spc), tokens);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
