/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:01:32 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/25 15:04:46 by owalsh           ###   ########.fr       */
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
# include <string.h>

// MS LIBRARIES
# include "structs.h"
# include "defines.h"

// global

extern t_global g_global; 

/*
**
** INIT
**
*/
int	ms_init(t_data *data, char **argv, char **env);
/*
**
** LEXER
**
*/
int	ms_lexer(char *str, t_token **tokens);
int	tokenize(t_token **tokens, char *str, int *i, int type);
int	is_isspace(char c);
int	is_quote(char *str, int *type);
int	is_oper(char c1, char c2, int *type);
int	is_special(char c, int *type);
void	add_token(t_token *new, t_token **tokens);
char	*copy_chars(char *str, int *i, int n);
char	*copy_word(char *str, int *i);
char	*copy_quote(char *str, int *i);
int	lexer_checker(t_token *head);
/*
**
** EXPANSER
**
*/
int		ms_expanser(t_token **token);
int		expanse_var(t_token **tokens);
int		expanse_quote(t_token **tokens);
void	insert_token(t_token **tokens, t_token *new);
/*
**
** CLEAN
**
*/
void	clean(t_data *data);
void	free_list(t_token **tokens);
/*
**
** UTILS
**
*/
char	*ft_strncpy(char *dst, char *src, int n);
void	display_tokens();
void	display_specific_tokens(t_token *head);
int		err_msg(int	err, char c);

#endif