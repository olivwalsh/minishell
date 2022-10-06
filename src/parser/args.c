/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:50:18 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/06 18:49:01 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_newargs(t_token **token, t_cmd *new, int i)
{
	new->args = malloc(sizeof(char *) * (i + 1));
	if (!new->args)
	{
		err_msg_str(MALLOC_ERR);
		return ;
	}
	i = 0;
	while (*token && !is_delim(*token) && !is_redir(*token))
	{
		new->args[i] = copy_cmd(token);
		i++;
		*token = (*token)->next;
	}
	new->args[i] = NULL;
}

static void	cmd_updateargs(t_token **token, t_cmd *new, int i)
{
	char	**args;
	int		j;

	args = malloc(sizeof(char *) * (i + ft_tablen(new->args) + 1));
	j = 0;
	while (new->args && new->args[j])
	{
		args[j] = new->args[j];
		j++;
	}
	while (*token && !is_delim(*token) && !is_redir(*token))
	{
		args[j] = copy_cmd(token);
		j++;
		*token = (*token)->next;
	}
	args[j] = NULL;
	free(new->args);
	new->args = args;
}

void	cmd_setargs(t_token **token, t_cmd *new)
{
	int		i;
	t_token	*tmp;

	if (*token && !new->cmd)
	{
		new->cmd = copy_cmd(token);
		check_builtin(new);
		if (!new->builtin)
			new->cmd = get_cmdpath(new->cmd);
	}
	i = 0;
	tmp = *token;
	while (tmp && !is_delim(tmp) && !is_redir(tmp))
	{
		i++;
		tmp = tmp->next;
	}
	if (!new->args)
		cmd_newargs(token, new, i);
	else
		cmd_updateargs(token, new, i);
}
