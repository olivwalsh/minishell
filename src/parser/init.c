/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:41:47 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/08 11:41:50 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	memset(redir, 0, sizeof(t_redir));
	if (!redir)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	return (redir);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_cmd));
	new->fd_in = -1;
	new->fd_out = -1;
	new->redir = NULL;
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

t_cmd	*create_cmd(t_token **token)
{
	t_cmd	*new;

	new = init_cmd();
	while (*token && !is_delim(*token))
	{
		if (is_redir(*token) && (*token)->next && (*token)->next->type == WORD)
			cmd_addredir(token, new);
		else if ((*token)->type == WORD)
			cmd_setargs(token, new);
		else
		{
			err_msg_str(-3, "missing command after redirection.\n");
			return (NULL);
		}
	}
	return (new);
}