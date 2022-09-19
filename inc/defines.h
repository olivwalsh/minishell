/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:22:28 by owalsh            #+#    #+#             */
/*   Updated: 2022/09/19 16:38:58 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define ERROR_LEXER -1

# define BUFFER_SIZE 1

// Colours
# define RED "\033[1;31m"
# define ORANGE	"\e[38;5;166m"
# define GREEN "\033[1;32m"
# define RESET "\033[m"
# define LRED "\033[1;31m"
# define LGREEN	"\033[1;32m"
# define LYELLOW	"\033[1;33m"
# define YELLOW	"\033[0;33m"
# define BLUE "\033[0;34m"
# define LBLUE "\033[1;34m"
# define PURPLE	"\033[0;35m"
# define LPURPLE "\033[1;35m"
# define CYAN "\033[0;36m"
# define LCYAN "\033[1;36m"
# define LGREY "\033[0;37m"
# define WHITE "\033[1;37m"
# define PINK "\e[38;5;205m"
# define LPINK "\e[38;4;200m"

// PROMT
# define SUCESS_PROMPT "\033[1;32m\u2794\033[1;31m  m\033[1;31mi\033[1;33m\
n\033[0;33mi\033[1;32ms\033[1;32mh\033[1;34me\e[38;4;200ml\033[1;35ml\033[m$ "
# define FAIL_PROMPT "\033[1;31m\u2794\033[1;31m  m\033[1;31mi\033[1;33m\
n\033[0;33mi\033[1;32ms\033[1;32mh\033[1;34me\e[38;4;200ml\033[1;35ml\033[m$ "

// Tokens type
# define WORD 1
# define PIPE 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define OPEN_BRK 5
# define CLOSE_BRK 6
# define DBL_QUOTE 7
# define SGL_QUOTE 8
# define VAR 9
# define OPERAND 10
# define OPEROR 11
# define APPEND_IN 12
# define APPEND_OUT 13

// Chars decimal value
# define DQUOTE 34
# define SQUOTE 39

// BUILTINS
# define BD_ECHO 101
# define BD_CD 102
# define BD_PWD 103
# define BD_EXPORT 104
# define BD_UNSET 105
# define BD_ENV 106
# define BD_EXIT 107

// Keys
# define KEY_CTRLC 3
# define KEY_CTRLD 4
# define KEY_CTRLQ 28

#endif