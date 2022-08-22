/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:01:32 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/22 15:54:01 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

// SYSTEM LIBRARIES
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

// MS LIBRARIES
# include "structs.h"
# include "defines.h"

/*
**
** INIT
**
*/
int	ms_init(t_data *data, int argc, char **argv, char **env);

#endif