/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:23:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 14:43:47 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bracket_checker(t_token *head)
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
			if ((str[i] == '(' || str[i] == ')') && is_brk_problem(str[i], tmp))
			{
				str[i + 1] = '\0';
				return (err_msg(-1, &str[i], 1));
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
