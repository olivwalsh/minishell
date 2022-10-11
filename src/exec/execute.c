/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 10:03:13 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(t_cmdlst **cmds, char **env, int *ex)
{
	int	res;

	res = EXIT_SUCCESS;
	if (!*cmds)
		return (res);
	if (!env)
		return (EXIT_FAILURE);
	if ((*cmds)->type == WORD
		&& (((*cmds)->next && (*cmds)->next->type == PIPE)
			|| ((*cmds)->prev && (*cmds)->prev->type == PIPE)))
		set_fd(*cmds);
	if ((*cmds)->type == WORD)
		res = exec_cmd(cmds, env, ex);
	if ((*cmds)->type == OPEN_BRK)
		res = ms_bracket(&(*cmds)->next, env, ex);
	else if ((*cmds)->next && (*cmds)->next->type == OPEN_BRK)
		res = ms_bracket(&(*cmds)->next->next, env, ex);
	if ((*cmds)->next && (*cmds)->next->type == OPERAND && !res)
		res = ms_execute(&(*cmds)->next, env, ex);
	else if ((*cmds)->next && (*cmds)->next->type == OPEROR && res)
		res = ms_execute(&(*cmds)->next, env, ex);
	else if ((*cmds)->next
		&& (*cmds)->next->type != OPEROR && (*cmds)->next->type != OPERAND)
		res = ms_execute(&(*cmds)->next, env, ex);
	return (res);
}

int	ms_exec(t_cmdlst **cmds, char **env)
{
	int	res;
	int	ex;

	ex = 0;
	res = ms_execute(cmds, env, &ex);
	res = ms_wait(cmds, res);
	if (ex)
		exit(res);
	return (res);
}
