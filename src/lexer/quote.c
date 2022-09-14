/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:38:40 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/14 21:34:09 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_stop(char *stop, int n)
{
	int	i;
	
	i = 0;
	while (i <= n)
		stop[i++] = '\0';
}

int	quote_init(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == DBL_QUOTE)
		{
			tmp->qts_stop = malloc(sizeof(char) * (ft_strlen(tmp->value) + 1));
			if (!tmp->qts_stop)
			{
				err_msg(-2, 0);
				return (EXIT_FAILURE);
			}
			fill_stop(tmp->qts_stop, ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
