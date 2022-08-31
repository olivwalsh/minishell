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

static int	check_var(t_token **tokens, char *var)
{
	printf("var is %s\n", var);
	if (!var[1] || is_isspace(var[1]))
	{
		(*tokens)->var = -1;
		return (1);
	}	
	return (0);
}

// static char	*get_var(t_token **tokens, char *var)
// {

// 	if (check_var(tokens, var))
// 		return (var);
// 	var++;
// 	str = getenv(var++);
// 	return (str);
// }

static void	check_new(t_token *new)
{
	t_token	*tmp;

	tmp = new;
	while (tmp)
	{
		if (tmp->value[0] == '$')
			tmp->var = -1;
		tmp = tmp->next;
	}
}

int	expanse_var(t_token **tokens)
{
	t_token	*new;
	char	*str;
	char	*var;

	new = NULL;
	// str = get_var(tokens, (*tokens)->value);
	var = (*tokens)->value;
	if (check_var(tokens, var))
		return (EXIT_SUCCESS);
	var++;
	str = getenv(var++);
	// if ((*tokens)->var == -1)
	// 	return (EXIT_SUCCESS);
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
