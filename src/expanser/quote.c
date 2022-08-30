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

static int	is_delimiter(char *str)
{
	char	*special;
	int		i;

	i = 0;
	special = "|<>\'\"&()";
	printf("in is_delimiter, with str[0] = %c\n", str[0]);
	while (str && str[i] && (str[i] > 32 && str[i] < 127) \
		&& !strchr(special, str[i]))
	{
		if (str[i] == '$' && is_delimiter(&str[i + 1]))
			break ;
		i++;
	}
	return (i);
}

int	is_var(t_token **tokens, char *str, int i)
{
	int	j;

	j = 0;
	if ((*tokens)->exp == i)
		return (0);
	if (str[0] == '$')
	{
		printf("found a dollar\n");
		if (!str[1])
			return (0);
		j = is_delimiter(&str[1]);
		printf("delimiter is at %d char \n", j);
		return (j);
	}
	return (0);
}


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

int	expanse_quote(t_token **tokens, char *str)
{
	char	*var;
	char	*val;
	char	*exp;
	int		i;
	int		j;

	var = NULL;
	exp = NULL;
	i = 0;
	j = 0;
	while (str && str[i])
	{
		j = is_var(tokens, &str[i], i);
		if (j)
		{
			var = malloc(sizeof(char) * (j + 1));
			if (!var)
				return (EXIT_FAILURE);
			var = ft_strncpy(var, &str[i + 1], j);
			val = getenv(var);
			if (val[0] == '$')
				(*tokens)->exp = i;
			free(var);
			str[i] = 0;
			exp = ft_strjoin(exp, str);
			exp = ft_strjoin(exp, val);
			i += j + 1;
			exp = ft_strjoin(exp, &str[i]);
			free((*tokens)->value);
			(*tokens)->value = exp;
			return (EXIT_SUCCESS);
		}
		else
			i++;	
	}
	(*tokens)->exp = -1;
	return (EXIT_SUCCESS);
}
