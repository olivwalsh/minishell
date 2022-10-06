/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:07:15 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 11:42:26 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_readinfile(t_token **token, t_cmd *cmd)
{
	cmd->redir->redir_in = 1;
	*token = (*token)->next;
	if (!(*token))
	{
		err_msg_str(SYNTAX_ERR);
		return (EXIT_FAILURE);
	}
	cmd->redir->infile = copy_cmd(token);
	if (!read_file(cmd->redir->infile))
	{
		*token = (*token)->next;
		return (EXIT_FAILURE);
	}
	cmd->fd_in = read_file(cmd->redir->infile);
	*token = (*token)->next;
	return (EXIT_SUCCESS);
}

int	cmd_readstdin(t_token **token, t_cmd *cmd)
{
	set_heredocterm();
	cmd->redir->append_in = 1;
	*token = (*token)->next;
	if (!(*token))
	{
		err_msg_str(SYNTAX_ERR);
		return (EXIT_FAILURE);
	}
	cmd->redir->delimiter = copy_cmd(token);
	cmd->fd_in = fork_stdin(cmd->redir->delimiter);
	*token = (*token)->next;
	return (EXIT_SUCCESS);
}

int	cmd_writeoutfile(t_token **token, t_cmd *cmd)
{
	cmd->redir->redir_out = 1;
	*token = (*token)->next;
	if (!(*token))
	{
		err_msg_str(SYNTAX_ERR);
		return (EXIT_FAILURE);
	}
	cmd->redir->outfile = copy_cmd(token);
	if (!create_file(cmd->redir->outfile))
	{
		*token = (*token)->next;
		return (EXIT_FAILURE);
	}
	cmd->fd_out = create_file(cmd->redir->outfile);
	*token = (*token)->next;
	return (EXIT_SUCCESS);
}

int	cmd_appendoutfile(t_token **token, t_cmd *cmd)
{
	cmd->redir->append_out = 1;
	*token = (*token)->next;
	if (!(*token))
	{
		err_msg_str(SYNTAX_ERR);
		return (EXIT_FAILURE);
	}
	cmd->redir->outfile = copy_cmd(token);
	if (!append_file(cmd->redir->outfile))
	{
		*token = (*token)->next;
		return (EXIT_FAILURE);
	}
	cmd->fd_out = append_file(cmd->redir->outfile);
	*token = (*token)->next;
	return (EXIT_SUCCESS);
}

int	cmd_addredir(t_token **token, t_cmd *cmd)
{
	if (!cmd->redir)
		cmd->redir = create_redir();
	if ((*token)->type == REDIR_IN)
		return (cmd_readinfile(token, cmd));
	else if ((*token)->type == APPEND_IN)
		return (cmd_readstdin(token, cmd));
	else if ((*token)->type == REDIR_OUT)
		return (cmd_writeoutfile(token, cmd));
	else if ((*token)->type == APPEND_OUT)
		return (cmd_appendoutfile(token, cmd));
	return (EXIT_SUCCESS);
}
