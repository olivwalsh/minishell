/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:58:51 by foctavia          #+#    #+#             */
/*   Updated: 2022/08/29 17:30:45 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	check_var(t_token **tokens, char *var)
// {
// 	if (!var[1] || is_isspace(var[1]))
// 	{
// 		(*tokens)->var_stop = -1;
// 		return (1);
// 	}	
// 	return (0);
// }

static void	check_new(t_token *new)
{
	t_token	*tmp;

	tmp = new;
	while (tmp)
	{
		if (tmp->value[0] == '$')
			tmp->var_stop = -1;
		tmp = tmp->next;
	}
}

static int	expanse_var(t_token **tokens)
{
	t_token	*new;
	char	*str;
	char	*var;

	new = NULL;
	var = (*tokens)->value;
	// if (check_var(tokens, var))
	// 	return (EXIT_SUCCESS);
	var++;
	str = getenv(var++);
	if (!str)
	{
		(*tokens)->value = NULL;
		(*tokens)->type = 0;
		return (EXIT_SUCCESS);
	}
	ms_lexer(str, &new);
	if (!new)
		return (EXIT_FAILURE);
	check_new(new);
	insert_token(tokens, new);
	return (EXIT_SUCCESS);
}

int	var_expanser(t_token **tokens)
{
	int			res;
	t_token		*tmp;

	res = 0;
	tmp = *tokens;
	while (tmp && !g_global.data->err)
	{
		if (tmp->type == VAR)
			res = expanse_var(&tmp);
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == VAR && tmp->var_stop > -1)
			res = var_expanser(tokens);
		tmp = tmp->next;
	}
	return (res);
}
