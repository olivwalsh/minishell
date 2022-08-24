/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:13:21 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/24 12:15:02 by owalsh           ###   ########.fr       */
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
			if (tmp && tmp->value)
				printf("token->value = %s\t\ttoken->type = %d\n\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
	}
	else
		printf("Tokens list is empty\n");
}
