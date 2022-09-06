/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:08:05 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/06 15:15:50 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(t_token **token)
{
	t_cmd	*new;
	char	*args;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_cmd));
	new->fd_in = -1;
	new->fd_out = -1;
	new->redir = NULL;
	if (is_redir(*token))
		cmd_addredir(token, new);
	if ((*token) && (is_redir(*token) || is_delim(*token)))
	{
		err_msg_str(-1, (*token)->value);
		return (NULL);
	}
	new->cmd = (*token)->value;
	args = NULL;
	while ((*token) && !is_delim(*token) && !is_redir(*token))
	{
		args = ft_strjoin(args, (*token)->value, 1);
		args = ft_strjoin(args, " ", 1);
		*token = (*token)->next;
	}
	new->args = ft_split(args, ' ');
	free(args);
	if (*token && ((*token)->type == REDIR_OUT || (*token)->type == APPEND_OUT))
		cmd_addredir(token, new);
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
