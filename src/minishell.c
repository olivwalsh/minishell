/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 13:51:13 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {NULL};

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		res;

	if (argc != 1)
		return (EXIT_FAILURE);
	if (ms_init(&data, argv, env))
		return (EXIT_FAILURE);
	res = 0;
	while (1)
	{
		if (!res)
			data.shell.input = readline(SUCESS_PROMPT);
		else
			data.shell.input = readline(FAIL_PROMPT);
		if (data.shell.input[0] && !ms_lexer(data.shell.input, &data.tokens)
			&& !ms_expanser(&data.tokens))
		{
			// display_tokens();
			ms_parser(data.tokens, &data.cmds);
			// display_cmds();
			ms_execute(&data.cmds, data.shell.env);
			res = ms_wait(&data.cmds);
		}
		add_history(data.shell.input);
		clean(&data);
	}
	return (EXIT_SUCCESS);
}
