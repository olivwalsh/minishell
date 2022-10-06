/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:13:13 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/06 15:29:07 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanse_tilde(t_token **token)
{
	char	*var;

	if ((*token)->value && (*token)->value[0] && !(*token)->value[1])
	{
		var = "HOME";
		(*token)->value = ft_getenv(var);
		if (!(*token)->value)
		{
			delete_token(token);
			return (EXIT_SUCCESS);
	}
	}
	return (EXIT_SUCCESS);
}