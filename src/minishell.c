/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/25 19:15:37 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {NULL};

int main(int argc, char **argv, char **env)
{
	t_data	data;
	int		res;

	if (argc != 1)
		return (EXIT_FAILURE);
	ms_init(&data, argv, env);
	while (1)
	{
		res = 0;
		data.shell.input = readline(PROMPT);
		res = ms_lexer(data.shell.input, &data.tokens);
		ms_exit(data.shell.input, NULL);
		if (!res)
		{
			ms_expanser(&data.tokens);
			display_tokens();
			printf("_________________________________________________________\n\n");
			// parser
			// execution
		}
		add_history(data.shell.input);
		clean(&data);
	}
	return (EXIT_SUCCESS);
}
