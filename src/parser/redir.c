/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:07:15 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/07 10:08:08 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_readinfile(t_token **token, t_cmd *cmd)
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
	return (EXIT_SUCCESS);
}

int	cmd_readstdin(t_token **token, t_cmd *cmd)
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
	return (EXIT_SUCCESS);
}

int	cmd_writeoutfile(t_token **token, t_cmd *cmd)
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
	return (EXIT_SUCCESS);
}

int	cmd_appendoutfile(t_token **token, t_cmd *cmd)
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
	return (EXIT_SUCCESS);
}

int	cmd_addredir(t_token **token, t_cmd *cmd)
{
	if (!cmd->redir)
		cmd->redir = create_redir();
	if ((*token)->type == REDIR_IN)
		cmd_readinfile(token, cmd);
	else if ((*token)->type == APPEND_IN)
		cmd_readstdin(token, cmd);
	else if ((*token)->type == REDIR_OUT)
		cmd_writeoutfile(token, cmd);
	else if ((*token)->type == APPEND_OUT)
		cmd_appendoutfile(token, cmd);
	return (EXIT_SUCCESS);
}
