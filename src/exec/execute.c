/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 19:54:50 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_bracket(t_cmdlst **cmds, char **env)
{
	int	res;

	res = EXIT_SUCCESS;
	while (*cmds && (*cmds)->type != CLOSE_BRK)
	{
		if ((*cmds)->type == WORD)
			res = exec_cmd(cmds, env);
		if ((*cmds)->next && (*cmds)->next->next && (*cmds)->next->type == OPERAND && !res)
			*cmds = (*cmds)->next->next;
		else if ((*cmds)->next && (*cmds)->next->next && (*cmds)->next->type == OPEROR && res)
			*cmds = (*cmds)->next->next;
		else
			break ;
	}
	while (*cmds && (*cmds)->type != CLOSE_BRK)
		*cmds = (*cmds)->next;
	return (res);
}

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
	// if ((*cmds)->next && (*cmds)->next->type == CLOSE_BRK)
	// 	return (res);
	if ((*cmds)->next && (*cmds)->next->type == OPERAND && !res)
		res = ms_execute(&(*cmds)->next, env);
	else if ((*cmds)->next && (*cmds)->next->type == OPEROR && res)
		res = ms_execute(&(*cmds)->next, env);
	else if ((*cmds)->next && (*cmds)->next->type != OPEROR && (*cmds)->next->type != OPERAND)
		res = ms_execute(&(*cmds)->next, env);
	return (res);
}
