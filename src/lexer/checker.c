/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:44:58 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/25 14:52:48 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	brackets_count(t_token *head)
{
	t_token	*tmp;
	char	*str;
	int		i;
	int		open_brackets;
	int		close_brackets;

	tmp = head;
	open_brackets = 0;
	close_brackets = 0;
	while (tmp)
	{
		i = 0;
		str = tmp->value;
		while (tmp->type != DBL_QUOTE && tmp->type != SGL_QUOTE && str && str[i])
		{
			if (str[i] == '(')
				open_brackets++;
			else if (str[i] == ')')
				close_brackets++;
			i++;
		}
		tmp = tmp->next;	
	}
	if (close_brackets - open_brackets > 0)
		err_msg(-1, ')');
	else if (close_brackets - open_brackets < 0)
		err_msg(-1, '(');
	return (close_brackets - open_brackets);
}

int	lexer_checker(t_token *head)
{
	if (brackets_count(head))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
