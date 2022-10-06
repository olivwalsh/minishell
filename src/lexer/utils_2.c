/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 14:43:12 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 14:43:32 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_phrase(t_token *token)
{
	if (token && (token->type == WORD || token->type == SGL_QUOTE \
		|| token->type == DBL_QUOTE))
		return (1);
	return (0);
}

static int	is_connector(t_token *token)
{
	if (token && (token->type == OPERAND || token->type == OPEROR \
		|| token->type == PIPE))
		return (1);
	return (0);
}

int	is_brk_problem(char c, t_token *tmp)
{
	if ((c == '(' && tmp->next && tmp->next->type == CLOSE_BRK) \
		|| (c == '(' && tmp->prev && !is_connector(tmp->prev)) \
		|| (c == ')' && tmp->prev && !is_phrase(tmp->prev)))
		return (1);
	return (0);
}
