/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:07:15 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 16:24:54 by owalsh           ###   ########.fr       */
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



void	sig_prompt(int signum)
{
	(void)signum;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_heredocterm()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_global.data->terminal.heredoc);
	// signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, &sig_prompt); 	// ctrl - C

	//signal(SIGEOF, &sig_eof); // ctrl - D
    // signal(SIGINT, &sig_prompt);	// ctrl - C
}

int	cmd_readstdin(t_token **token, t_cmd *cmd)
{
	set_heredocterm();
	cmd->redir->append_in = 1;
	*token = (*token)->next;
	if (!(*token))
	{
		err_msg_str(-1, NULL);
		return (EXIT_FAILURE);
	}
	cmd->redir->delimiter = copy_cmd(token);
	cmd->fd_in = read_stdin(cmd->redir->delimiter);
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
		err_msg_str(-1, NULL);
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
		cmd_readinfile(token, cmd);
	else if ((*token)->type == APPEND_IN)
		cmd_readstdin(token, cmd);
	else if ((*token)->type == REDIR_OUT)
		cmd_writeoutfile(token, cmd);
	else if ((*token)->type == APPEND_OUT)
		cmd_appendoutfile(token, cmd);
	return (EXIT_SUCCESS);
}
