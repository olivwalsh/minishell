/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:39:53 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/30 15:45:46 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	cmd_delimiter(int type)
{
	if (type == PIPE || type == OPERAND || type == OPEROR)
		return (1);
	return (0);
}

t_cmd	*create_cmd(char *cmd)
{
	t_cmd	*new;
	char	**split_cmd;

	new = malloc(sizeof(t_cmd));
	if (!new || !cmd)
		return (NULL);
	split_cmd = ft_split(cmd, ' ');
	if (split_cmd && split_cmd[0]) 
		new->cmd = split_cmd[0];
	if (split_cmd[1])
		new->args = &split_cmd[1];
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
	return (new);
}

int	ms_parser(t_token *token, t_cmdlst **cmds)
{
	t_token		*tmp;
	char		*str;
	

	tmp = token;
	printf("in ms_parser\n");
	while (tmp)
	{	
		str = NULL;
		printf("tmp->value = %s\n", tmp->value);
		while (tmp && !cmd_delimiter(tmp->type))
		{
			printf("is a cmd\n");
			str = ft_strjoin(str, tmp->value);
			if (tmp->next && !cmd_delimiter(tmp->next->type))
			{
				str = ft_strjoin(str, " ");
				tmp = tmp->next;
			}
			else
				break;
		}
		add_cmdlst(cmds, create_cmdlst(tmp->type, create_cmd(str)));
		free(str);
		if (tmp)
			tmp = tmp->next;
	}
	display_cmds();
	return (EXIT_SUCCESS);
}
