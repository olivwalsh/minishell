/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/22 15:53:38 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **env)
{
	t_data data;

	
	ms_init(&data, argc, argv, env);
	// setup readline
	while (1)
	{
		data.shell.input = readline("minishell$ ");
		printf("%s\n", data.shell.input);
		add_history(data.shell.input);
		free(data.shell.input);
	}
	return (EXIT_SUCCESS);
}
