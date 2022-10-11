/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 14:37:48 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global = {NULL};

static void	ms_minishell(t_data *data, int *res)
{
	int	exstatus;

	exstatus = *res;
	if (data->shell.input)
		free(data->shell.input);
	set_terminal(&data->terminal);
	if (*res)
		data->shell.input = readline(FAIL_PROMPT);
	else
		data->shell.input = readline(SUCESS_PROMPT);
	if (!ms_lexer(data->shell.input, &data->tokens, res)
		&& !ms_expanser(&data->tokens, res, exstatus)
		&& !ms_parser(data->tokens, &data->cmds, res))
		*res = ms_exec(&data->cmds, data->shell.env);
	add_history(data->shell.input);
	clean(data);
}

int	ms_error(void)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, "wrong usage: ./minishell echo coucou\n", 38);
	write(STDERR_FILENO, "minishell: correct usage: ./minishell\n", 39);
	write(STDERR_FILENO, "-> minishell$ echo coucou\n", 27);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		res;

	if (argc != 1)
		return (ms_error());
	if (ms_init(&data, argv, env, &res))
		return (EXIT_FAILURE);
	while (1)
		ms_minishell(&data, &res);
	return (EXIT_SUCCESS);
}
