/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:08:26 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/01 10:56:56 by owalsh           ###   ########.fr       */
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
			free(tmp->value);
			free(tmp);
			tmp = NULL;
			tmp = next;
		}
		*tokens = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab && tab[i])
	{
		while (i < get_tablen(tab))
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
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
				if (tmp->cmd->cmd_args)
					free_tab(tmp->cmd->cmd_args);
				if (tmp->cmd->cmd)
					free(tmp->cmd->cmd);
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
	if (data)
	{
		if (data->tokens)
			free_tokens(&data->tokens);
		
		if (data->cmds)
			free_cmds(&data->cmds);
		if (data->shell.input)
			free(data->shell.input);
	}
	if (g_global.data)
		g_global.data->err = 0;
}
