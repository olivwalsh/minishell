/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:50:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/04 17:34:56 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_wait(t_cmdlst **cmds, int res)
{
	int			error;
	int			exit_status;
	t_cmdlst	*tmp;

	error = 0;
	while ((*cmds)->prev)
		*cmds = (*cmds)->prev;
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->cmd)
		{
			waitpid(tmp->cmd->pid, &exit_status, 0);
			if (WIFEXITED(exit_status))
				error = WEXITSTATUS(exit_status);
			if (error)
				return (error);
		}
		tmp = tmp->next;
	}
	return (res);
}
