/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:51 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 19:11:24 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parser(t_token *tokens, t_cmdlst **cmds, int *res)
{
	t_token	*tmp;
	char	c[2];

	tmp = tokens;
	while (tmp && !g_global.data->err)
	{
		c[0] = tmp->value[0];
		c[1] = '\0';
		if (!tmp->prev && is_delim(tmp) == 1)
		{
			*res = err_msg(-1, c, 0);
			return (res);
		}
		if (is_delim(tmp) == 1 && (tmp->next && is_delim(tmp->next) == 1))
		{
			*res = err_msg(-1, c, 0);
			return (res);
		}
		if (!is_delim(tmp))
			add_cmdlst(cmds, create_cmdlst(WORD, create_cmd(&tmp)));
		else
		{
			add_cmdlst(cmds, create_cmdlst(tmp->type, NULL));
			tmp = tmp->next;
		}
	}
	if (!(*res))
		*res = g_global.data->err;
	return (*res);
}
