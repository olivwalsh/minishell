/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/29 12:29:04 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_expanser(t_token **token)
{
	static int	counter;
	int			res;
	t_token		*tmp;

	res = 0;
	tmp = *token;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == VAR)
			res = expanse_var(&tmp);
		else if (tmp->type == DBL_QUOTE)
			res = expanse_quote(&tmp);
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	tmp = *token;
	while (tmp)
	{
		if ((tmp->type == DBL_QUOTE || tmp->type == VAR) && tmp->exp > -1)
			res = ms_expanser(token);
		tmp = tmp->next;
	}
	return (res);
}
