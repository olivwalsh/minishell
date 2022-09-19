/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:00:00 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/19 14:00:36 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_bracket(t_cmdlst **cmds, char **env)
{
	int	res;

	res = EXIT_SUCCESS;
	while (*cmds && (*cmds)->type != CLOSE_BRK)
	{
		if ((*cmds)->next && (*cmds)->next->type == PIPE)
			set_fd(cmds);
		if ((*cmds)->type == WORD)
			res = exec_cmd(cmds, env);
		if ((*cmds)->next && (*cmds)->next->next && (*cmds)->next->type == OPERAND && !res)
			*cmds = (*cmds)->next->next;
		else if ((*cmds)->next && (*cmds)->next->next && (*cmds)->next->type == OPEROR && res)
			*cmds = (*cmds)->next->next;
		else
			break ;
	}
	while (*cmds && (*cmds)->prev->type != CLOSE_BRK)
		*cmds = (*cmds)->next;
	return (res);
}
