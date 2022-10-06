/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:44:58 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 11:30:01 by foctavia         ###   ########.fr       */
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
		err_msg(SYNTAX_ERR, ')', 1);
	else if (count < 0)
		err_msg(SYNTAX_ERR, '(', 1);
	if (count != 0 || order != 0)
		return (EXIT_FAILURE);
	if (brk_placement(head))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	redir_checker(t_token *head)
{
	t_token *tmp;

	tmp = head;
	while (tmp)
	{
		if (is_redir(tmp) && tmp->next && is_redir(tmp->next))
			return (err_msg(SYNTAX_ERR, tmp->value[0], 1));
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
