/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:35 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/30 18:33:00 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_type(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == SGL_QUOTE || tmp->type == DBL_QUOTE)
			tmp->type = WORD;
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	is_variable(char *str)
{
	int	j;

	j = 0;
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
		return (err_msg_str(-2, 0));
	var = ft_strncpy(var, &str[i + 1], j);
	val = ft_getenv(var);
	free(var);
	return (val);
}

char	*get_expanse(t_token *tokens, char *str, char *val, int *i)
{
	char	*exp;
	int		j;

	j = *i;
	exp = NULL;
	exp = ft_strjoin(exp, str, 1);
	if (val)
		exp = ft_strjoin(exp, val, 1);
	*i = ft_strlen(exp);
	exp = ft_strjoin(exp, &str[j], 1);
	free(tokens->value);
	tokens->value = exp;
	return (exp);
}

int	expanse_quote(t_token *tokens, char *str)
{
	char		*val;
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (str && str[i])
	{
		j = is_variable(&str[i]);
		if (j)
		{
			val = NULL;
			val = get_value(str, i, j);
			if (g_global.data->err)
				return (EXIT_FAILURE);
			str[i] = 0;
			i += j + 1;
			str = get_expanse(tokens, str, val, &i);
			free(val);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
