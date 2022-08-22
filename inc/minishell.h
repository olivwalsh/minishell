/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:01:32 by owalsh            #+#    #+#             */
/*   Updated: 2022/08/22 14:35:07 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

#endif

// str = cat Makefile|grep -i"SRC"|wc -c>$VAR

// | > < $ " ' && || ( ) + isspace()

// " this is a '$VAR' string " => 

/*

// linked list (next/prev) => LEXER

cat		=> WORD
Makefile => WORD
|		=> PIPE
grep	=> WORD
-i		=> WORD
"SRC"	=> DOUBLE QUOTES
|		=> 	PIPE
wc		=> WORD
-c		=> WORD
>		=> REDIR OUT
$VAR	=> VAR

// EXPANSER

cat
Makefile
|
grep
-i
SRC
|
wc
-c
>
variable
VAR
value


// PARSER

Cmd1 => cat Makefile

Cmd2 => grep -i SRC

Cm3 => wc -c

*/


/*
structure TOKENS
{
	value (WORD)
	type
	*prev
	*next
}


structure CMDS
{
	INfd
	OUTfd
	cmd
	args
	RedirIN (true/false)
	RedirOUT (true/false)

}

*/