/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:44:58 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 19:02:17 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	brk_order(t_token *head)
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

static int	brk_count(t_token *head)
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

static int	brk_placement(t_token *head)
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

int	lexer_checker(t_token *head)
{
	int	count;
	int	order;

	count = brk_count(head);
	order = brk_order(head);
	if (count > 0 || count != order)
		err_msg(-1, ")", 1);
	else if (count < 0)
		err_msg(-1, "(", 1);
	if (count != 0 || order != 0)
		return (EXIT_FAILURE);
	if (brk_placement(head))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
