/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/24 20:43:42 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_expanser(t_token **token)
{
	int		res;
	t_token	*tmp;
	
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
		if(tmp->type == VAR && tmp->type == DBL_QUOTE)
			ms_expanser(token);
		tmp = tmp->next;
	}
	return (res);
}