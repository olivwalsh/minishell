/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:35 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/30 15:23:03 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	delete_quote(t_token **tokens)
// {
// 	char	*dest;
// 	char	*src;

// 	src = (*tokens)->value;
// 	src++;
// 	dest = malloc(sizeof(char) * (strlen((*tokens)->value - 1)));
// 	ft_strncpy(dest, src, strlen((*tokens)->value) - 2);
// 	if (!dest)
// 	{
// 		(*tokens)->value = NULL;
// 		(*tokens)->type = 0;
// 	}
// 	free((*tokens)->value);
// 	(*tokens)->value = NULL;
// 	(*tokens)->value = dest;
// 	return (EXIT_SUCCESS);
// }

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;
	int		i;
	int		j;

	if ((!s1 && !s2) || !s2[0])
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	return (new);
}

int	*ft_tabint(const int *t, int c)
{
	int		i;
	int		*tab;

	tab = (int *)t;
	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
			return (tab + i);
		i++;
	}
	return (NULL);
}

int	is_var(t_token *tokens, char *str, int i)
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

void	get_expanse(t_token *tokens, char *str, char *val, int i)
{
	char	*exp;

	exp = NULL;
	exp = ft_strjoin(exp, str);
	if (val)
		exp = ft_strjoin(exp, val);
	exp = ft_strjoin(exp, &str[i]);
	free(tokens->value);
	tokens->value = exp;
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

int	expanse_quote(t_token *tokens, char *str, int idx)
{
	char		*val;
	int			i;
	int			j;

	i = 0;
	j = 0;
	printf("str is %s\nidx is %d\n", str, idx);
	while (str && str[i])
	{
		j = is_var(tokens, &str[i], i);
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
