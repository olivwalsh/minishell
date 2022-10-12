/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:00:00 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/12 12:27:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_bracket(t_cmdlst **cmds, char **env, int *ex)
{
	int	res;

	res = EXIT_SUCCESS;
	while (*cmds && (*cmds)->type != CLOSE_BRK)
	{
		if (*cmds && (*cmds)->type == WORD
			&& (((*cmds)->next && (*cmds)->next->type == PIPE)
				|| ((*cmds)->prev && (*cmds)->prev->type == PIPE)))
			set_fd(*cmds);
		if (*cmds && (*cmds)->type == WORD)
			res = exec_cmd(cmds, env, ex);
		if (*cmds && (*cmds)->next
			&& (*cmds)->next->next && (*cmds)->next->type == OPERAND && !res)
			*cmds = (*cmds)->next->next;
		else if (*cmds && (*cmds)->next
			&& (*cmds)->next->next && (*cmds)->next->type == OPEROR && res)
			*cmds = (*cmds)->next->next;
		else
			break ;
	}
	while (*cmds && (*cmds)->prev && (*cmds)->prev->type != CLOSE_BRK)
		*cmds = (*cmds)->next;
	return (res);
}
