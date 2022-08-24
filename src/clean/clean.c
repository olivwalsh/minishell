/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:08:26 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/24 16:46:12 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_list(t_token **tokens)
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

void	clean(t_data *data)
{
	if (data)
	{
		if (data->tokens)
			free_list(&data->tokens);
		if (data->shell.input)
			free(data->shell.input);
	}
	if (g_global.data)
		g_global.data->err = 0;
}
