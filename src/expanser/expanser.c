/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/11 19:15:10 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_expanser(t_token **tokens, int *res)
{
	t_token		*tmp;

	tmp = *tokens;
	while (tokens && tmp && !g_global.data->err)
	{
		if (tmp->type == WORD && !ft_strncmp("~", tmp->value, 1))
			*res = expanse_tilde(&tmp);
		if (tmp->type == WORD && has_wildcard(tmp->value))
			*res = expanse_wildcard(&tmp);
		if (tmp)
			tmp = tmp->next;
	}
	return (*res);
}

static int	quote_expanser(t_token **tokens, int *res)
{
	t_token		*tmp;

	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == DBL_QUOTE)
			*res = expanse_quote(tmp, tmp->value);
		tmp = tmp->next;
	}
	return (*res);
}

static int	var_expanser(t_token **tokens, int *res, int exstatus)
{
	t_token		*tmp;

	tmp = *tokens;
	while (tokens && tmp && !g_global.data->err)
	{
		if (tmp->type == VAR && !ft_strncmp("$?", tmp->value, 2))
			*res = expanse_exstatus(&tmp, exstatus);
		if (tmp->type == VAR && tmp->var_stop > -1)
			*res = expanse_var(&tmp, res);
		if (tmp)
			tmp = tmp->next;
	}
	tmp = *tokens;
	while (tokens && tmp && !*res)
	{
		if (tmp->type == VAR && tmp->var_stop > -1)
			*res = var_expanser(tokens, res, exstatus);
		if (tmp->spc)
			tmp->value = add_space(tmp->value);
		tmp = tmp->next;
	}
	return (*res);
}

int	ms_expanser(t_token **tokens, int *res, int exstatus)
{
	if (!*res && !var_expanser(tokens, res, exstatus))
	{
		if (!*res && !quote_expanser(tokens, res))
		{
			if (!*res && !word_expanser(tokens, res))
			{
				if (!change_type(tokens))
					return (EXIT_SUCCESS);
			}
		}
	}
	return (EXIT_FAILURE);
}
