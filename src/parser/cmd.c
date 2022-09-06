/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:08:05 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/06 13:13:52 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_token *token)
{
	t_cmd	*new;
	t_token	*tmp;
	char	**args;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	tmp = token;
	if (tmp->type == REDIR_IN || tmp->type == APPEND_IN)
		cmd_read(&tmp, new);
	else if (tmp->type == REDIR_OUT || tmp->type == APPEND_OUT)
		cmd_write(&tmp, new);
	if (tmp && (is_redir(tmp) || is_delimiter(tmp)))
		return (err_msg_str(-1, tmp->value));
	new->cmd = tmp;
	args = NULL;
	while (!is_delimiter(tmp) && !is_redir(tmp))
	{
		args = ft_strjoin(args, tmp->value, 1);
		args = ft_strjoin(args, " ", 1);
		tmp = tmp->next;
	}
	new->args = ft_split(args, ' ');
	if (tmp && tmp->type == REDIR_OUT || tmp->type == APPEND_OUT)
		cmd_write(&tmp, new);
	if (g_global.data->err)
		return (NULL);
	return (new);
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
