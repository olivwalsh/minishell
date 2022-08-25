/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:35 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/24 15:21:03 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanse_quote(t_token **tokens)
{
	t_token	*new;
	char	*dest;
	char	*src;

	new = NULL;
	src = (*tokens)->value;
	src++;
	dest = malloc(sizeof(char) * (strlen((*tokens)->value - 1)));
	ft_strncpy(dest, src, strlen((*tokens)->value) - 2);
	if (!dest)
	{
		(*tokens)->value = NULL;
		(*tokens)->type = 0;
	}
	ms_lexer(dest, &new);
	if (!new)
	{
		free(dest);
		return (EXIT_FAILURE);
	}
	insert_token(tokens, new);
	free(dest);
	return (EXIT_SUCCESS);
}