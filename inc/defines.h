/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foctavia <foctavia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:22:28 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/23 18:58:43 by foctavia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_DEFINES_H
#define MS_DEFINES_H

# define ERROR_LEXER -1

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define RESET "\033[m"

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