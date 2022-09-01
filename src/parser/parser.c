/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:39:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/31 16:42:24 by owalsh           ###   ########.fr       */
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
		return (NULL);
	new->type = type;
	new->cmd = cmd;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int	ms_parser(t_token *token, t_cmdlst **cmds)
{
	t_token		*tmp;
	char		*str;

	tmp = token;
	while (tmp)
	{	
		str = NULL;
		while (tmp && !cmd_delimiter(tmp->type))
		{
			str = ft_sjoin(str, tmp->value);
			if (tmp->next && !cmd_delimiter(tmp->next->type))
			{
				str = ft_sjoin(str, " ");
				tmp = tmp->next;
			}
			else
				break ;
		}
		add_cmdlst(cmds, create_cmdlst(tmp->type, create_cmd(str)));
		free(str);
		if (tmp)
			tmp = tmp->next;
	}
	display_cmds();
	return (EXIT_SUCCESS);
}
