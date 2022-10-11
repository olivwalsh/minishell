/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:14:38 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/11 19:15:21 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_space(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		err_msg_str(MALLOC_ERR);
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = ' ';
	new[i + 1] = '\0';
	free(str);
	return (new);
}

int	has_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
