/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:38:40 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/01 15:38:43 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_minus(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = -2;
		i++;
	}
	str[n] = -2;
}

int	quote_init(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == DBL_QUOTE)
		{
			tmp->qts_stop = malloc(sizeof(int) * (ft_strlen(tmp->value) + 1));
			ft_minus(tmp->qts_stop, ft_strlen(tmp->value));
			if (!tmp->qts_stop)
			{
				err_msg(-2, 0);
				return (EXIT_FAILURE);
			}
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
