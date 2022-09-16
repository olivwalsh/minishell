/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:48:08 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/16 16:17:34 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*non_quote(char *dest, char *src, int type)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src && src[i])
	{
		if (src[i] == type)
			i++;
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
	return (dest);
}

int	quote_exist(char *src)
{
	int	i;
	int	j;
	int	type;

	i = 0;
	j = 0;
	type = 0;
	while (src && src[i])
	{
		if (src[i] == DQUOTE || src[i] == SQUOTE)
		{
			j = i;
			j++;
			while (src && src[j])
			{
				if (src[j] == src[i])
					type = src[j];
				j++;
			}
			break ;
		}
		i++;
	}
	return (type);
}

char	*delete_quotes(char *src)
{
	char	*dest;
	int		type;

	type = quote_exist(src);
	if (!type)
		return (src);
	dest = malloc(sizeof(char) * (ft_strlen(src) - 1));
	if (!dest)
	{
		free(src);
		return (err_msg_str(-2, NULL));
	}
	dest = non_quote(dest, src, type);
	free(src);
	return (dest);
}
