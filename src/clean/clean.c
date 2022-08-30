/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:08:26 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/30 15:45:04 by owalsh           ###   ########.fr       */
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
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
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
			// if (tmp->cmd && tmp->cmd->args)
			// 	free_tab(tmp->cmd->args);
			if (tmp->cmd)
			{
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
