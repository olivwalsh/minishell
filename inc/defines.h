/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:22:28 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/25 16:22:07 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEFINES_H
#define MS_DEFINES_H

# define ERROR_LEXER -1

# define RED "\033[1;31m"
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

# define DQUOTE 34
# define SQUOTE 39

#endif