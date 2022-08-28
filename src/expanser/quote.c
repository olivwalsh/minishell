/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:35 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/28 21:00:11 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_var(t_token *tokens)
{
	char	*dest;
	char	*src;
	char	*str;
	int		i;
	int		j;

	printf("inside replace\n");
	src = tokens->value;
	src++;
	dest = malloc(sizeof(char) * (strlen(tokens->value - 1)));
	if (!dest)
		return(err_msg(-2, 0));
	ft_strncpy(dest, src, strlen(tokens->value) - 2);
	dest++;
	str = getenv(dest++);
	printf("str is %s\n", str);
	if (!str)
	{
		tokens->value = "''";
		return (EXIT_SUCCESS);
	}
	free(dest);
	dest = malloc(sizeof(char) * (strlen(str) + 3));
	if (!dest)
		return(err_msg(-2, 0));
	dest[0] = '\'';
	i = 1;
	j = 0;
	while (str[j])
		dest[i++] = str[j++]; 
	dest[i++] = '\'';
	dest[i] = '\0';
	free(tokens->value);
	tokens->value = dest;
	return (EXIT_SUCCESS);
}

static int	check_quote(t_token *new)
{
	t_token	*tmp;
	int		res;

	res = 0;
	tmp = new;
	while (tmp)
	{
		if (tmp->type == SGL_QUOTE && tmp->value[1] == '$')
			res = replace_var(tmp);
		tmp = tmp->next;
	}
	return (res);
}

int	expanse_quote(t_token **tokens)
{
	t_token	*new;
	char	*dest;
	char	*src;

	new = NULL;
	(*tokens)->exp = 1;
	src = (*tokens)->value;
	src++;
	dest = malloc(sizeof(char) * (strlen((*tokens)->value - 1)));
	ft_strncpy(dest, src, strlen((*tokens)->value) - 2);
	if (!dest)
	{
		(*tokens)->value = NULL;
		(*tokens)->type = 0;
	}
	ms_lexer(dest, &new);
	if (!new)
	{
		free(dest);
		return (EXIT_FAILURE);
	}
	if (check_quote(new))
		return (EXIT_FAILURE);
	insert_token(tokens, new);
	free(dest);
	return (EXIT_SUCCESS);
}