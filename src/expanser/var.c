/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/10/07 16:33:38 by foctavia         ###   ########.fr       */
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
	str = ft_getenv(var++);
	if (!str)
	{
		delete_token(tokens);
		return (EXIT_SUCCESS);
	}
	if (ms_lexer(str, &new, res))
		return (EXIT_FAILURE);
	if (!new)
		return (EXIT_FAILURE);
	if (str)
		free(str);
	check_new(new, *tokens);
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}

int	expanse_exstatus(t_token **tokens, int exstatus)
{
	free((*tokens)->value);
	(*tokens)->value = ft_itoa(exstatus);
	(*tokens)->type = WORD;
	return (EXIT_SUCCESS);
}
