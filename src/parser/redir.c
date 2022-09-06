/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:07:15 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/06 13:12:42 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

int cmd_read(t_token **token, t_cmd *cmd)
{
	// check if fd is already set
	// return error if yes
	// create fd
	// return
	if ((*token)->type == REDIR_IN)
	{
		cmd->redir->redir_in = 1;
		*token = (*token)->next;
		if (!(*token))
		{
			err_msg_str(-1, NULL);
			return (EXIT_FAILURE);
		}
		cmd->redir->infile = (*token)->value;
		*token = (*token)->next;
	}
	else if ((*token)->type == APPEND_IN)
	{
		cmd->redir->append_in = 1;
		*token = (*token)->next;
		if (!(*token))
		{
			err_msg_str(-1, NULL);
			return (EXIT_FAILURE);
		}
		cmd->redir->delimiter = (*token)->value;
		*token = (*token)->next;
	}
	return (EXIT_SUCCESS);
}

int cmd_write(t_token **token, t_cmd *cmd)
{
	if ((*token)->type == REDIR_OUT)
	{
		cmd->redir->redir_out = 1;
		*token = (*token)->next;
		if (!(*token))
		{
			err_msg_str(-1, NULL);
			return (EXIT_FAILURE);
		}
		cmd->redir->outfile = (*token)->value;
		*token = (*token)->next;
	}
	else if ((*token)->type == APPEND_OUT)
	{
		cmd->redir->append_out = 1;
		*token = (*token)->next;
		if (!(*token))
		{
			err_msg_str(-1, NULL);
			return (EXIT_FAILURE);
		}
		cmd->redir->outfile = (*token)->value;
		*token = (*token)->next;
	}
	return (EXIT_SUCCESS);
}
