/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:16:56 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/22 15:45:28 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef MS_STRUCTS_H
#define MS_STRUCTS_H

// TOKENS
typedef struct	s_token
{
	char			*value;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

// COMMANDS
typedef struct	s_cmd
{
	int				fd_in;
	int				fd_out;
	char			*cmd;
	char			**args;
	int				redir_in;
	int				redir_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

// TERMINAL -- termios
typedef struct	s_terminal
{
	struct termios	dftl;
	struct termios	new;
}				t_terminal;


// SHELL -- minishell data
typedef struct	s_shell
{
	char		**env;
	char		*input;
	
}				t_shell;

// GLOBAL (variable)
typedef struct	s_data
{
	t_shell			shell;
	t_terminal		terminal;
	t_cmd			*cmd;		// linked list
	t_token			*tokens;	// linked list
}				t_data;

#endif