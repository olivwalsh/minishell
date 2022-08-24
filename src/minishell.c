/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/24 16:44:19 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {NULL};

int main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1)
		return (EXIT_FAILURE);
	ms_init(&data, argv, env);
	// setup readline
	while (1)
	{
		data.shell.input = readline(GREEN"minishell$ "RESET);
		// create tokens
		ms_lexer(data.shell.input, &data.tokens);
		display_tokens();
		add_history(data.shell.input);
		// expanser
		// parser
		// execution
		clean(&data);
	}
	return (EXIT_SUCCESS);
}
