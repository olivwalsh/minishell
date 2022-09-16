/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:12:16 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 11:53:22 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *token)
{
	if (token->type == REDIR_IN || token->type == REDIR_OUT
		|| token->type == APPEND_IN || token->type == APPEND_OUT)
		return (1);
	return (0);
}

int	is_delim(t_token *token)
{
	if (token->type == PIPE || token->type == OPERAND || token->type == OPEROR)
		return (1);
	else if (token->type == OPEN_BRK || token->type == CLOSE_BRK)
		return (2);
	return (0);
}

int	ft_strtoken(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
		{
			j = i;
			while (str[i] == ' ' && str[i + 1])
				i++;
			if (!str[i + 1])
				return (j);
		}
		i++;
	}
	return (i);
}
