/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:39:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/06 10:09:37 by owalsh           ###   ########.fr       */
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

int	add_redir(char **cmd_args, t_redir *redir)
{
	if (!ft_strcmp("<", cmd_args[0]))
	{
		redir->redir_in = 1;
		if (!(cmd_args[1]))
		{
			err_msg_str(-1, cmd_args[1]);
			return (EXIT_FAILURE);
		}
		redir->infile = cmd_args[1];
	}
	else if (!ft_strcmp(cmd_args[0], ">"))
	{
		redir->redir_out = 1;
		if (!(cmd_args[1]))
		{
			err_msg_str(-1, cmd_args[1]);
			return (EXIT_FAILURE);
		}
		redir->outfile = cmd_args[1];
	}
	return (EXIT_SUCCESS);	
}

int	add_append(char **cmd_args, t_redir *redir)
{
	if (!ft_strcmp(cmd_args[0], "<<"))
	{
		redir->append_in = 1;
		if (!(cmd_args[1]))
		{
			err_msg_str(-1, cmd_args[1]);
			return (EXIT_FAILURE);
		}
		redir->delimiter = cmd_args[1];
	}
	else if (!ft_strcmp(cmd_args[0], ">>"))
	{
		redir->append_out = 1;
		if (!cmd_args[1])
		{
			err_msg_str(-1, cmd_args[1]);
			return (EXIT_FAILURE);
		}
		redir->outfile = cmd_args[1];
	}
	return (EXIT_SUCCESS);	
}

t_redir	*create_redir()
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

t_cmd	*create_cmd(char *str)
{
	t_cmd	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	new = malloc(sizeof(t_cmd));
	if (!new || !str)
		return (NULL);
	new->cmd_args = ft_split(str, ' ');
	new->redir = create_redir();
	// if start with redir or append, start i = 2 otherwise i = 0
	if (!add_redir(&new->cmd_args[0], new->redir)
		|| !add_append(&new->cmd_args[0], new->redir))
			i += 2;
	// if there is an actual command
	if (new->cmd_args[i] && !is_redir(new->cmd_args[i]))
	{
		new->cmd = get_cmdpath(new->cmd_args[i]);
	// go to the end of the command
		i++;
		j = i;
		if (new->cmd_args[i])
		{
			while (new->cmd_args[i] && !is_redir(new->cmd_args[i]))
				i++;
			new->args = malloc(sizeof(char *) * (i - j + 1));
			k = 0;
			while (j < i)
			{
				new->args[k] = new->cmd_args[j];
				k++;
				j++;
			}
			new->args[k] = NULL;
		}
	}
	// if ends with a redir
	if (new->cmd_args[i] && is_redir(new->cmd_args[i]))
	{
		add_redir(&new->cmd_args[i], new->redir);
		add_append(&new->cmd_args[i], new->redir);
	}
	if (g_global.data->err)
		return (NULL);
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
/*
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
*/