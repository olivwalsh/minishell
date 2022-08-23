/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/23 18:50:06 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Init global variable

t_global g_global = { NULL };

void	free_list(t_token *tokens)
{
	t_token	*tmp;
	t_token	*next;
	
	if (tokens)
	{
		tmp = tokens;
		while (tmp && tmp->next)
		{
			next = tmp->next;
			free(tmp->value);
			free(tmp);
			tmp = next;
		}
		free(tmp->value);
		free(tmp);
	}
}

void	clean(t_data *data)
{
	if (data)
	{
		if (data->tokens)
			free_list(data->tokens);
		if (data->shell.input)
			free(data->shell.input);
	}
}

int main(int argc, char **argv, char **env)
{
	t_data data;

	ms_init(&data, argc, argv, env);
	// setup readline
	while (1)
	{
		data.shell.input = readline("minishell$ ");
		ms_lexer(data.shell.input, &data.tokens);
		display_tokens();
		add_history(data.shell.input);
		clean(&data);
	}
	return (EXIT_SUCCESS);
}
