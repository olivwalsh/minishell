/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:08:26 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/10 16:24:46 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;
	t_token	*next;

	if (*tokens)
	{
		tmp = *tokens;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->value)
			{
				free(tmp->value);
				tmp->value = NULL;
			}
			free(tmp);
			tmp = NULL;
			tmp = next;
		}
		*tokens = NULL;
	}
}

void	free_tab(char **table)
{
	int	i;

	i = 0;
	if (table)
	{
		while (table && table[i])
		{
			if (table[i])
			{
				free(table[i]);
				table[i] = NULL;
			}
			i++;
		}
		free(table);
		table = NULL;
	}
}

void	free_redir(t_redir *redir)
{
	if (redir->infile)
		free(redir->infile);
	if (redir->delimiter)
		free(redir->delimiter);
	if (redir->outfile)
		free(redir->outfile);
	free(redir);
}

void	free_cmds(t_cmdlst **lst)
{
	t_cmdlst	*tmp;
	t_cmdlst	*next;

	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			next = tmp->next;
			if (tmp->cmd)
			{
				if (tmp->cmd->redir)
					free_redir(tmp->cmd->redir);
				if (tmp->cmd->cmd)
					free(tmp->cmd->cmd);
				if (tmp->cmd->args)
					free_tab(tmp->cmd->args);
				free(tmp->cmd);
			}
			free(tmp);
			tmp = NULL;
			tmp = next;
		}
		*lst = NULL;
	}
}

void	clean(t_data *data)
{
	tcsetattr(0, TCSANOW, &data->terminal.dftl);
	if (data)
	{
		if (data->tokens)
			free_tokens(&data->tokens);
		if (data->cmds)
			free_cmds(&data->cmds);
	}
	if (g_global.data)
		g_global.data->err = 0;
}
