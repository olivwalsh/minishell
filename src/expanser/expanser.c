/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:13:33 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/30 15:17:44 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_expanser(t_token **tokens)
{
	static int	idx;
	int			res;
	t_token		*tmp;

	res = 0;
	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == VAR)
			res = expanse_var(&tmp);
		else if (tmp->type == DBL_QUOTE)
			res = expanse_quote(tmp, tmp->value, idx++);
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if ((tmp->type == DBL_QUOTE && !ft_tabint(tmp->qts, -1)) \
			|| (tmp->type == VAR && tmp->var > -1))
			res = ms_expanser(tokens);
		tmp = tmp->next;
	}
	return (res);
}

// int	expanse(t_token	**tmp)
// {
// 	static int	idx;
// 	int			res;

// 	res = 0;
// 	if ((*tmp)->type == VAR)
// 		res = expanse_var(tmp);
// 	else if ((*tmp)->type == DBL_QUOTE)
// 		res = expanse_quote(*tmp, (*tmp)->value, idx++);
// 	return (res);
// }

// int	ms_expanser(t_token **token)
// {
// 	int			res;
// 	t_token		*tmp;

// 	res = 0;
// 	tmp = *token;
// 	while (tmp && !g_global.data->err)
// 	{
// 		if (tmp->type == VAR || tmp->type == DBL_QUOTE)
// 		{
// 			res = expanse(&tmp);
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	tmp = *token;
// 	while (tmp)
// 	{
// 		if ((tmp->type == DBL_QUOTE && !ft_tabint(tmp->qts, -1))
// 			|| (tmp->type == VAR && tmp->var > -1))
// 			res = ms_expanser(token);
// 		tmp = tmp->next;
// 	}
// 	return (res);
// }
