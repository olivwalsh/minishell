/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/24 17:10:56 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanse_quote(t_token **tokens)
{
	(void)tokens;
	return (0);
}

void	insert_token(t_token **tokens, t_token **new)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = *tokens;
	tmp1->prev->next = *new;
	(*new)->prev = tmp1->prev;
	if ((*new)->next)
	{
		tmp2 = *new;
		while(tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = tmp1->next;
		tmp1->next->prev = tmp2;
	}
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
	// printf("str is %s\n", str);
	if (!str)
	{
		(*tokens)->value = NULL;
		(*tokens)->type = 0;
	}
	ms_lexer(str, &new);
	if (!new)
		return (EXIT_FAILURE);
	insert_token(tokens, &new);
	return (0);
}

int	ms_expanser(t_token **token)
{
	int		res;
	t_token	*tmp;
	
	res = 0;
	tmp = *token;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == VAR)
			res = expanse_var(&tmp);
		else if (tmp->type == DBL_QUOTE)
			res = expanse_quote(&tmp);
		tmp = tmp->next;
	}
	tmp = *token;
	while (tmp)
	{
		if(tmp->type == VAR || tmp->type == DBL_QUOTE)
			ms_expanser(token);
		tmp = tmp->next;
	}
	return (res);
}