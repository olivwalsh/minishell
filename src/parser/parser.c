/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:39:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/05 13:15:48 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_delimiter(int type)
{
	if (type == PIPE || type == OPERAND || type == OPEROR \
		|| type == OPEN_BRK || type == CLOSE_BRK)
		return (1);
	return (0);
}

t_cmd	*create_cmd(char *str)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new || !str)
		return (NULL);
	new->cmd_args = ft_split(str, ' ');
	if (new->cmd_args && new->cmd_args[0])
		new->cmd = get_cmdpath(new->cmd_args[0]);
	if (new->cmd_args[1])
		new->args = &new->cmd_args[1];
	return (new);
}

void	add_cmdlst(t_cmdlst **lst, t_cmdlst	*new)
{
	t_cmdlst	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	else
		*lst = new;
}

t_cmdlst	*create_cmdlst(int type, t_cmd *cmd)
{
	t_cmdlst	*new;

	new = malloc(sizeof(t_cmdlst));
	if (!new)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	new->type = type;
	new->cmd = cmd;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	check_first(t_token *token)
{
	if (token->type == PIPE || token->type == OPERAND || token->type == OPEROR)
		return (err_msg(-1, token->value[0]));
	return (0);
}

int	parse_cmd(t_token **token, t_cmdlst **cmds)
{
	char		*str;

	str = NULL;
	while (*token && !cmd_delimiter((*token)->type) && !g_global.data->err)
	{
		str = ft_strjoin(str, (*token)->value, 1);
		if (!str)
			return (EXIT_FAILURE);
		if ((*token)->next && !cmd_delimiter((*token)->next->type))
		{
			str = ft_strjoin(str, " ", 1);
			if (!str)
				return (EXIT_FAILURE);
			*token = (*token)->next;
		}
		else
			break ;
	}
	add_cmdlst(cmds, create_cmdlst((*token)->type, create_cmd(str)));
	if (g_global.data->err)
		return (EXIT_FAILURE);
	free(str);
	return (EXIT_SUCCESS);
}	

int	ms_parser(t_token *token, t_cmdlst **cmds)
{
	t_token		*tmp;
	int			res;

	res = 0;
	tmp = token;
	while (tmp && !g_global.data->err)
	{	
		if (!tmp->prev)
			res = check_first(tmp);
		res = parse_cmd(&tmp, cmds);
		if (tmp)
			tmp = tmp->next;
	}
	display_cmds();
	return (res);
}
