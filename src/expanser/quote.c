/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:35 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/30 13:39:59 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_quote(t_token **tokens)
{
	char	*dest;
	char	*src;

	src = (*tokens)->value;
	src++;
	dest = malloc(sizeof(char) * (strlen((*tokens)->value - 1)));
	ft_strncpy(dest, src, strlen((*tokens)->value) - 2);
	if (!dest)
	{
		(*tokens)->value = NULL;
		(*tokens)->type = 0;
	}
	free((*tokens)->value);
	(*tokens)->value = NULL;
	(*tokens)->value = dest;
	return (EXIT_SUCCESS);
}

int	expanse_quote(t_token **tokens)
{
	char	str;
	char	var;
	int		i;

	var = NULL;
	str = (*tokens)->value;

}