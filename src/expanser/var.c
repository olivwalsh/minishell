/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/12 08:38:38 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_new(t_token *new, t_token *token)
{
	t_token	*tmp;

	tmp = new;
	while (tmp)
	{
		if (tmp->value[0] == '$')
		{
			tmp->var_stop = -1;
			tmp->type = WORD;
			tmp->value = add_space(tmp->value);
		}
		if (!tmp->next)
			tmp->spc = token->spc;
		tmp = tmp->next;
	}
}

char	*copy_words(char *str, int *i)
{
	int		j;
	char	*value;

	j = 0;
	while (str && str[j] && (str[j] > 31 && str[j] < 127))
	{
		if (str[j] == ' ' && str[j + 1] > 32 && str[j + 1] < 127)
		{
			j++;
			break ;
		}
		j++;
	}
	value = malloc(sizeof(char) * (j + 1));
	if (!value)
		return (err_msg_str(MALLOC_ERR));
	value = ft_strncpy(value, str, j);
	*i += j;
	return (value);
}

int	ms_word(char *str, t_token **tokens, int *res)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (*res);
	while (str && str[i] && !g_global.data->err)
	{
		while (str[i] && is_isspace(str[i]))
			i++;
		if (str[i])
			add_token(create_token(WORD, copy_words(&str[i], &i), 0), tokens);
	}
	if (g_global.data->err)
		*res = EXIT_FAILURE;
	return (*res);
}

void	delete_token(t_token **tokens)
{
	t_token	*prev;
	t_token	*next;

	prev = (*tokens)->prev;
	next = (*tokens)->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free((*tokens)->value);
	free(*tokens);
	*tokens = NULL;
	if (prev)
		*tokens = prev;
	if (!prev && !next)
	{
		tokens = NULL;
		g_global.data->tokens = NULL;
	}
}

int	expanse_var(t_token **tokens, int *res)
{
	t_token	*new;
	char	*str;
	char	*var;

	new = NULL;
	var = (*tokens)->value;
	var++;
	str = NULL;
	str = ft_getenv(var++);
	if (!str || !str[0])
	{
		delete_token(tokens);
		return (EXIT_SUCCESS);
	}
	if (ms_word(str, &new, res))
		return (EXIT_FAILURE);
	if (!new)
		return (EXIT_FAILURE);
	if (str)
		free(str);
	check_new(new, *tokens);
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}
