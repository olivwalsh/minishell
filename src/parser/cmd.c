/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:08:05 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/16 11:54:33 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_words(char *str, int *code)
{
	int	j;
	int	k;

	j = 0;
	if (!str[j])
		return (j);
	while (str && str[j])
	{
		if (str[j] == ' ')
		{
			k = j;
			while (str && str[j] && str[j] == ' ')
				j++;
			if (!str[j])
			{
				*code = 1;
				return (k);
			}
		}
		j++;
	}
	return (j);
}

int	count_words(t_token **token)
{
	int		i;
	int		code;
	char	*str;
	t_token	*tmp;

	i = 0;
	code = 0;
	str = (*token)->value;
	if (!str[i])
		return (i);
	i = loop_words(str, &code);
	if (code)
		return (i);
	tmp = *token;
	while (tmp->next && tmp->next->type == WORD && tmp->next->value[0] != '-')
	{
		str = tmp->next->value;
		i += loop_words(str, &code);
		if (code)
			return (i);
		tmp = tmp->next;
	}
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
		while ((*token)->next && (*token)->next->type == WORD && \
			(*token)->next->value[0] != '-')
		{
			join = ft_strjoin(join, (*token)->next->value, 1);
			*token = (*token)->next;
		}
		ft_strncpy(str, join, len);
		free(join);
	}
	str = delete_quotes(str);
	return (str);
}

void	check_builtin(t_cmd *new)
{
	if (!ft_strcmp(new->cmd, "echo"))
		new->builtin = BD_ECHO;
	else if (!ft_strcmp(new->cmd, "cd"))
		new->builtin = BD_CD;
	else if (!ft_strcmp(new->cmd, "pwd"))
		new->builtin = BD_PWD;
	else if (!ft_strcmp(new->cmd, "export"))
		new->builtin = BD_EXPORT;
	else if (!ft_strcmp(new->cmd, "unset"))
		new->builtin = BD_UNSET;
	else if (!ft_strcmp(new->cmd, "env"))
		new->builtin = BD_ENV;
	else if (!ft_strcmp(new->cmd, "exit"))
		new->builtin = BD_EXIT;
	else
		new->builtin = 0;
}

void	cmd_setargs(t_token **token, t_cmd *new)
{
	int		i;
	char	*args;
	t_token	*tmp;

	args = NULL;
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
	new->args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*token && !is_delim(*token) && !is_redir(*token))
	{
		new->args[i++] = copy_cmd(token);
		*token = (*token)->next;
	}
	new->args[i] = NULL;
	free(args);
}
