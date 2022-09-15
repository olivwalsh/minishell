/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:31:09 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/15 14:43:11 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_strncpy(dest, src, ft_strlen(tmp->value) - 2);
			if (!dest)
				tmp->value = NULL;
			free(tmp->value);
			tmp->value = add_space(dest);
			tmp->type = WORD;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
