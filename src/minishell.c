/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/30 19:00:08 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {NULL};

static void ms_minishell(t_data *data)
{
	int		res;

	res = 0;
	if (data->shell.input)
		free(data->shell.input);
	set_terminal(&data->terminal);
	if (res)
		data->shell.input = readline(FAIL_PROMPT);
	else
		data->shell.input = readline(SUCESS_PROMPT);
	if (!ms_lexer(data->shell.input, &data->tokens, &res)
		&& !ms_expanser(&data->tokens, &res)
		&& !ms_parser(data->tokens, &data->cmds, &res))
	{
		res = ms_execute(&data->cmds, data->shell.env);
		res = ms_wait(&data->cmds, res);
	}
	add_history(data->shell.input);
	clean(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc != 1)
		return (EXIT_FAILURE);
	if (ms_init(&data, argv, env))
		return (EXIT_FAILURE);
	while (1)
		ms_minishell(&data);
	return (EXIT_SUCCESS);
}
