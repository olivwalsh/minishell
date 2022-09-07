/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:08:05 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/07 18:50:17 by foctavia         ###   ########.fr       */
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

int	count_words(t_token **token)
{
	int	i;
	int	j;
	char	*str;
	t_token	*tmp;

	i = 0;
	j = 0;
	str = (*token)->value;
	while (str && str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	tmp = *token;
	while (tmp->next && tmp->next->type == WORD && tmp->next->value[0] != '-')
	{
		str = tmp->next->value;
		while (str && str[j])
		{
			if (str[j] == ' ')
				return (i);
			j++;
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

int	ft_strtoken(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != ' ')
		i++;
	return (i);
}

char	*copy_cmd(t_token **token)
{
	char	*str;
	char	*join;
	int		len;
	
	len = count_words(token);
	str = NULL;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (err_msg_str(-2, NULL));
	if (len == ft_strtoken((*token)->value))
		ft_strncpy(str, (*token)->value, len);
	else
	{
		join = NULL;
		join = ft_strjoin(join, (*token)->value, 1);
		while ((*token)->next && (*token)->next->type == WORD && (*token)->next->value[0] != '-')
		{
			join = ft_strjoin(join, (*token)->next->value, 1);
			*token = (*token)->next;
		}
		ft_strncpy(str, join, len);
		free(join);
	}
	return (str);
}

void    cmd_setargs(t_token **token, t_cmd *new)
{
    char    *args;
    t_token    *tmp;
    int        i;

    args = NULL;
    if (*token && !new->cmd)
        new->cmd = (*token)->value;
    *token =  (*token)->next;
    i = 0;
    tmp = *token;
    while (tmp && !is_delim(tmp) && !is_redir(tmp))
    {
        i++;
        tmp = tmp->next;
    }
    new->args = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while ((*token) && !is_delim(*token) && !is_redir(*token))
    {
        new->args[i++] = (*token)->value;
        *token = (*token)->next;
    }
    new->args[i] = NULL;
    free(args);
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
