/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:44:58 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/05 16:32:37 by owalsh           ###   ########.fr       */
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

int	redir_checker(t_token *head)
{
	t_token *tmp;
	char	first[2];

	tmp = head;
	while (tmp)
	{
		first[0] =  tmp->value[0];
		first[1] = '\0';
		if (is_redir(tmp) && tmp->next && is_redir(tmp->next))
			return (err_msg(-1, first, 1));
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	lexer_checker(t_token *head)
{
	if (bracket_checker(head))
		return (EXIT_FAILURE);
	if (redir_checker(head))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
