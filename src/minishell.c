/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:04 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/22 14:34:53 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	(void)env;
	char	*prompt_line;
	
	// setup readline
	prompt_line = readline("minishell$ ");
	printf("line read: %s", prompt_line);
	
	// setup your prompt

	// clean up
	free(prompt_line);

	return (EXIT_SUCCESS);
}
