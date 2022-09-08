/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:35 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/07 23:58:13 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable(t_token *tokens, char *str, int i)
{
	int	j;

	j = 0;
	if (ft_tabint(tokens->qts_stop, i))
		return (0);
	if (str[0] == '$')
	{
		if (!str[1])
			return (0);
		j = is_delimiter(&str[1]);
		return (j);
	}
	return (0);
}

char	*get_value(char *str, int i, int j)
{
	char	*var;
	char	*val;

	var = NULL;
	var = malloc(sizeof(char) * (j + 1));
	if (!var)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	var = ft_strncpy(var, &str[i + 1], j);
	val = getenv(var);
	free(var);
	return (val);
}

void	check_value(t_token *tokens, char *val, int idx, int i)
{
	int	j;

	j = 0;
	while (val && val[j])
	{
		if (val[j] == '$')
		{
			tokens->qts_stop[idx] = i + j;
			idx++;
		}
		j++;
	}
}

void	get_expanse(t_token *tokens, char *str, char *val, int i)
{
	char	*exp;

	exp = NULL;
	exp = ft_strjoin(exp, str, 1);
	if (val)
		exp = ft_strjoin(exp, val, 1);
	exp = ft_strjoin(exp, &str[i], 1);
	free(tokens->value);
	tokens->value = exp;
}

int	expanse_quote(t_token *tokens, char *str, int idx)
{
	char		*val;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		j = is_variable(tokens, &str[i], i);
		if (j)
		{
			val = get_value(str, i, j);
			if (g_global.data->err)
				return (EXIT_FAILURE);
			check_value(tokens, val, idx, i);
			str[i] = 0;
			i += j + 1;
			get_expanse(tokens, str, val, i);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	tokens->qts_stop[idx] = -1;
	return (EXIT_SUCCESS);
}
