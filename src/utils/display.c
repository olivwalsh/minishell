/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:13:21 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/24 17:00:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_tokens(void)
{
	t_token	*tmp;

	if (g_global.data->tokens)
	{
		tmp = g_global.data->tokens;
		while (tmp)
		{
			//if (tmp && tmp->value)
			//	printf("token->value = %s\t\ttoken->type = %d\n\n", tmp->value, tmp->type);
			if (tmp-> type == 1)
				printf("WORD");
			if (tmp->type == 2)
				printf(" | ");
			if (tmp->type == 3)
				printf(" < ");
			if (tmp->type == 4)
				printf(" > ");
			if (tmp->type == 5)
				printf(" ( ");
			if (tmp->type == 6)
				printf(" ) ");
			if (tmp->type == 7)
				printf(" \" ");
			if (tmp->type == 8)
				printf(" \' ");
			if (tmp->type == 9)
				printf(" $VAR ");
			if (tmp->type == 10)
				printf(" && ");
			if (tmp->type == 11)
				printf(" || ");
			if (tmp->type == 12)
				printf(" << ");
			if (tmp->type == 13)
				printf(" >> ");
			printf("\t\t%s\n", tmp->value);
			tmp = tmp->next;
		}
	}
	else
		printf("Tokens list is empty\n");
}
