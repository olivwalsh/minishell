/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:31:09 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/15 17:06:40 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*non_quote(char *dest, char *src)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (src && src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
			i++;
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
	return (dest);
}

int	delete_quote(t_token **tokens)
{
	char	*dest;
	char	*src;
	t_token	*tmp;

	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == SGL_QUOTE || tmp->type == DBL_QUOTE)
		{
			src = tmp->value;
			src++;
			dest = malloc(sizeof(char) * (ft_strlen(tmp->value) - 1));
			if (!dest)
				return (err_msg(-2, 0));
			dest = non_quote(dest, src);
			if (!dest)
				tmp->value = NULL;
			free(tmp->value);
			tmp->value = dest;
			tmp->type = WORD;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
