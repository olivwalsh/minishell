/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exstatus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:13:25 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/11 10:13:52 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expanse_exstatus(t_token **tokens, int exstatus)
{
	free((*tokens)->value);
	(*tokens)->value = ft_itoa(exstatus);
	(*tokens)->type = WORD;
	return (EXIT_SUCCESS);
}
