/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 18:10:00 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(t_cmdlst **cmds, char **env)
{
	int	res;

	res = EXIT_SUCCESS;
	if (!env)
		return (EXIT_FAILURE);
	if ((*cmds)->next && (*cmds)->next->type == PIPE)
		set_fd(cmds);
	if ((*cmds)->type == WORD)
		res = exec_cmd(cmds, env);
	if ((*cmds)->type == OPEN_BRK)
		res = ms_bracket(&(*cmds)->next, env);
	else if ((*cmds)->next && (*cmds)->next->type == OPEN_BRK)
		res = ms_bracket(&(*cmds)->next->next, env);
	if ((*cmds)->next && (*cmds)->next->type == OPERAND && !res)
		res = ms_execute(&(*cmds)->next, env);
	else if ((*cmds)->next && (*cmds)->next->type == OPEROR && res)
		res = ms_execute(&(*cmds)->next, env);
	else if ((*cmds)->next
		&& (*cmds)->next->type != OPEROR && (*cmds)->next->type != OPERAND)
		res = ms_execute(&(*cmds)->next, env);
	return (res);
}
