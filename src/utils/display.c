/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:13:21 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/30 15:44:04 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_cmd(t_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;	
	if (cmd)
	{
		printf("cmd = "GREEN"|"RESET"%s"GREEN"|"RESET"\n", cmd->cmd);
		args = cmd->args;
		while (args && args[i])
		{
			printf("arg: "GREEN"|"RESET"%s "GREEN"|"RESET, args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("no cmd\n");
}

void	display_cmds(void)
{
	t_cmdlst	*tmp;
	
	printf("DISPLAY CMDS\n\n");
	if (g_global.data->cmds)
	{
		printf("g_global.data->cmds = %p\n\n", g_global.data->cmds);
		tmp = g_global.data->cmds;
		while (tmp)
		{
			if (tmp)
				printf("\ntmp->prev = %p\t\ttmp = %p\t\ttmp->next = %p\n", tmp->prev, tmp, tmp->next);
			if (tmp->type == 1)
				printf("WORD");
			if (tmp->type == 2)
				printf(" | ");
			if (tmp->type == 3)
				printf(" < ");
			if (tmp->type == 4)
				printf(" > ");
			if (tmp->type == 5)
				printf(" ( ");
			if (tmp->type == 6)
				printf(" ) ");
			if (tmp->type == 10)
				printf(" && ");
			if (tmp->type == 11)
				printf(" || ");
			if (tmp->type == 12)
				printf(" << ");
			if (tmp->type == 13)
				printf(" >> ");
			if (tmp->type == WORD)
				display_cmd(tmp->cmd);
			tmp = tmp->next;
		}
	}
	else
		printf("no list of cmds\n");
}

void	display_tokens(void)
{
	t_token	*tmp;

	printf("DISPLAY TOKENS\n\n");
	if (g_global.data->tokens)
	{
		printf("g_global.data->tokens = %p\n\n", g_global.data->tokens);
		tmp = g_global.data->tokens;
		while (tmp)
		{
			//if (tmp && tmp->value)
			//	printf("token->value = %s\t\ttoken->type = %d\n\n", tmp->value, tmp->type);
			if (tmp-> type == 1)
				printf("WORD");
			if (tmp->type == 2)
				printf(" | ");
			if (tmp->type == 3)
				printf(" < ");
			if (tmp->type == 4)
				printf(" > ");
			if (tmp->type == 5)
				printf(" ( ");
			if (tmp->type == 6)
				printf(" ) ");
			if (tmp->type == 7)
				printf(" \" ");
			if (tmp->type == 8)
				printf(" \' ");
			if (tmp->type == 9)
				printf(" $VAR ");
			if (tmp->type == 10)
				printf(" && ");
			if (tmp->type == 11)
				printf(" || ");
			if (tmp->type == 12)
				printf(" << ");
			if (tmp->type == 13)
				printf(" >> ");
			printf("\t\t"GREEN"|"RESET"%s"GREEN"|"RESET"\n", tmp->value);
			tmp = tmp->next;
		}
	}
	else
		printf("Tokens list is empty\n");
}

void	display_specific_tokens(t_token *head)
{
	t_token	*tmp;

	printf("DISPLAY SPECIFIC TOKENS\n\n");
	if (head)
	{
		tmp = head;
		while (tmp)
		{
			printf("token->prev = %p\ttoken = %p\ttoken->next = %p\n", tmp->prev, tmp, tmp->next);
			if (tmp && tmp->value)
				printf("token->value = %s\t\ttoken->type = %d\n\n", tmp->value, tmp->type);
			tmp = tmp->next;
		}
	}
	else
		printf("Tokens list is empty\n");
}
