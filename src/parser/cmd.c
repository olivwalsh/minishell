/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:08:05 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/06 16:18:17 by owalsh           ###   ########.fr       */
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

void	cmd_setargs(t_token **token, t_cmd *new)
{
	char	*args;

	args = NULL;
	while ((*token) && !is_delim(*token) && !is_redir(*token))
	{
		args = ft_strjoin(args, (*token)->value, 1);
		args = ft_strjoin(args, " ", 1);
		*token = (*token)->next;
	}
	new->args = ft_split(args, ' ');
	free(args);
}

t_cmd	*create_cmd(t_token **token)
{
	t_cmd	*new;

	new = init_cmd();
	if (is_redir(*token))
		cmd_addredir(token, new);
	if ((*token) && (is_redir(*token) || is_delim(*token)))
	{
		err_msg_str(-1, (*token)->value);
		return (NULL);
	}
	new->cmd = (*token)->value;
	cmd_setargs(token, new);
	if (*token && ((*token)->type == REDIR_OUT || (*token)->type == APPEND_OUT))
		cmd_addredir(token, new);
	if (g_global.data->err)
		return (NULL);
	return (new);
}
