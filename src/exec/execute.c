/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 17:35:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/12 17:48:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute(t_cmdlst **cmds, char **env)
{
	if (!env)
		return (EXIT_FAILURE);
	if ((*cmds)->next && (*cmds)->next->type == PIPE)
		set_fd(cmds);
	if ((*cmds)->type == WORD)
		exec_cmd(cmds, env);
	if (*cmds && (*cmds)->next)
		ms_execute(&(*cmds)->next, env);
	return (EXIT_SUCCESS);
}
