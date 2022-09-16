/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 14:07:18 by foctavia         ###   ########.fr       */
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
	if ((*cmds)->next)
		res = ms_execute(&(*cmds)->next, env);
	return (res);
}
