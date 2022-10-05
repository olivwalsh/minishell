/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:38:51 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/05 09:54:26 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parser(t_token *tokens, t_cmdlst **cmds, int *res)
{
	t_token	*tmp;
	char	*str_char;

	tmp = tokens;
	while (!*res && tmp && !g_global.data->err)
	{
		str_char = ft_strndup(tmp->value, 1);
		if (!tmp->prev && is_delim(tmp) == 1)
		{
			*res = err_msg(-1, str_char, 0);
			return (*res);
		}
		if (is_delim(tmp) == 1 && (tmp->next && is_delim(tmp->next) == 1))
		{
			*res = err_msg(-1, str_char, 0);
			return (*res);
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
