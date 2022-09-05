/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/05 11:53:10 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quote_expanser(t_token **tokens)
{
	int			res;
	t_token		*tmp;

	res = 0;
	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == DBL_QUOTE && !ft_tabint(tmp->qts_stop, -1))
			res = expanse_quote(tmp, tmp->value, tmp->idx++);
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == DBL_QUOTE && !ft_tabint(tmp->qts_stop, -1))
			res = quote_expanser(tokens);
		tmp = tmp->next;
	}
	return (res);
}

static int	var_expanser(t_token **tokens)
{
	int			res;
	t_token		*tmp;

	res = 0;
	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == VAR)
			res = expanse_var(&tmp);
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == VAR && tmp->var_stop > -1)
			res = var_expanser(tokens);
		tmp = tmp->next;
	}
	return (res);
}

int	ms_expanser(t_token **tokens)
{
	if (!var_expanser(tokens))
	{
		if (!quote_expanser(tokens))
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
