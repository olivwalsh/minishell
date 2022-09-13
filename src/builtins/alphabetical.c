/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alphabetical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:47:09 by foctavia          #+#    #+#             */
/*   Updated: 2022/09/13 14:01:14 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env(char **env1, char **env2)
{
	char	*tmp;

	tmp = *env1;
	*env1 = *env2;
	*env2 = tmp;    
}

void	sort_env(int n, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (i < (n - 2))
	{
		j = i + 1;
		if (ft_strcmp(env[i], env[j]) > 0)
		{
			swap_env(&env[i], &env[j]);
			i = 0;
		}
		else
			i++;
	}
}

char	**dup_env(char **env)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (ft_tablen(env) + 1));
	if (!copy)
	{
		err_msg(-2, 0);
		return (NULL);
	}
	i = 0;
	while (env && env[i])
	{
		copy[i] = env[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	print_export(char **env)
{
	int		i;
	char	**copy;

	copy = dup_env(env);
	if (!copy)
		return (EXIT_FAILURE);
	sort_env(ft_tablen(copy), copy);
	i = 0;
	while (copy && copy[i])
	{
		printf("export %s\n", copy[i]);
		i++;
	}
	free(copy);
	return (EXIT_SUCCESS);
}
