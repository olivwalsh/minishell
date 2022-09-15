/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:21:20 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/15 14:32:40 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ms_echo(char *cmd, char **args)
{
    int    i;
    int    nl;

    nl = 1;
    if (ft_strcmp("echo", cmd))
        return (EXIT_FAILURE);
    i = 1;
    if (args[1] && !ft_strcmp(args[1], "-n"))
    {
        i = 2;
        nl = 0;
    }
    while (args && args[i])
    {
        printf("%s ", args[i]);
        i++;
    }
    if (nl)
        printf("\n");
    return (EXIT_SUCCESS);
}
