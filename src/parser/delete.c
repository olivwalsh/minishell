/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 11:48:08 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/06 11:43:30 by foctavia         ###   ########.fr       */
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

int	quote_exist(char *src, int *j)
{
	int	i;
	int	type;

	i = 0;
	*j = 0;
	type = 0;
	while (src && src[i])
	{
		if (src[i] == DQUOTE || src[i] == SQUOTE)
		{
			*j = i + 1;
			while (src && src[*j])
			{
				if (src[*j] == src[i])
				{
					type = src[(*j)++];
					break ;
				}
				(*j)++;
			}
			break ;
		}
		i++;
	}
	return (type);
}

char	*delete_quotes(char *src, char *rest)
{
	char	*dest;
	int		type;
	int		i;
	int		j;

	type = quote_exist(rest, &j);
	if (!type)
		return (src);
	dest = malloc(sizeof(char) * (ft_strlen(src) - 1));
	if (!dest)
	{
		free(src);
		return (err_msg_str(MALLOC_ERR));
	}
	dest = non_quote(dest, src, type);
	if (quote_exist(&rest[j], &i))
		dest = delete_quotes(dest, &dest[j - 2]);
	free(src);
	return (dest);
}
