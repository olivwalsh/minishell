/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:23:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/05 16:30:08 by owalsh           ###   ########.fr       */
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

int	brk_placement(t_token *head)
{
	t_token	*tmp;
	char	*str;
	int		i;
	int		brk;

	tmp = head;
	brk = 0;
	(void)brk;
	while (tmp)
	{
		i = 0;
		str = tmp->value;
		while (tmp->type != DBL_QUOTE \
			&& tmp->type != SGL_QUOTE && str && str[i])
		{
			if (str[i] == '(' || str[i] == ')')
			{
				if ((str[i] == '(' && tmp->next && tmp->next->type == CLOSE_BRK) \
					|| (str[i] == '(' && tmp->prev && !is_connector(tmp->prev)) \
					|| (str[i] == ')' && tmp->prev && !is_phrase(tmp->prev)))
				{
					str[i + 1] = '\0';
					return (err_msg(-1, &str[i], 1));
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	brk_order(t_token *head)
{
	t_token	*tmp;
	char	*str;
	int		i;
	int		open_brk;
	int		close_brk;

	tmp = head;
	open_brk = 0;
	close_brk = 0;
	while (tmp)
	{
		i = 0;
		str = tmp->value;
		while (tmp->type != DBL_QUOTE \
			&& tmp->type != SGL_QUOTE && str && str[i])
		{
			if (str[i] == '(' && open_brk == close_brk)
				open_brk++;
			else if (str[i] == ')' && open_brk != close_brk)
				close_brk++;
			i++;
		}
		tmp = tmp->next;
	}
	return (close_brk - open_brk);
}

int	brk_count(t_token *head)
{
	t_token	*tmp;
	char	*str;
	int		i;
	int		open_brk;
	int		close_brk;

	tmp = head;
	open_brk = 0;
	close_brk = 0;
	while (tmp)
	{
		i = 0;
		str = tmp->value;
		while (tmp->type != DBL_QUOTE \
			&& tmp->type != SGL_QUOTE && str && str[i])
		{
			if (str[i] == '(')
				open_brk++;
			else if (str[i] == ')')
				close_brk++;
			i++;
		}
		tmp = tmp->next;
	}
	return (close_brk - open_brk);
}
