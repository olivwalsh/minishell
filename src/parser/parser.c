/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:51 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 15:10:53 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parser(t_token *tokens, t_cmdlst **cmds, int *res)
{
	t_token	*tmp;

	tmp = tokens;
	while (!*res && tmp && !g_global.data->err)
	{
		if (!*res && (!tmp->prev || !tmp->next) && is_delim(tmp) == 1)
			*res = err_msg(SYNTAX_ERR, tmp->value[0], 0);
		if (!*res && is_delim(tmp) == 1 && \
			(tmp->next && is_delim(tmp->next) == 1))
			*res = err_msg(SYNTAX_ERR, tmp->value[0], 0);
		if (!*res && !is_delim(tmp))
			add_cmdlst(cmds, create_cmdlst(WORD, create_cmd(&tmp)));
		else if (!*res)
		{
			add_cmdlst(cmds, create_cmdlst(tmp->type, NULL));
			tmp = tmp->next;
		}
	}
	if (!(*res))
		*res = g_global.data->err;
	return (*res);
}
