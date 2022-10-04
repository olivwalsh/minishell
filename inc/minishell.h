/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owalsh <owalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:01:32 by owalsh            #+#    #+#             */
/*   Updated: 2022/10/04 12:17:24 by owalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// SYSTEM LIBRARIES
# include <stdio.h>
// #include "/usr/include/readline/readline.h"
// #include "/usr/include/readline/history.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>

// MS LIBRARIES
# include "structs.h"
# include "defines.h"

// global

extern t_global	g_global;

/*
**
** INIT
**
*/
int		ms_init(t_data *data, char **argv, char **env, int *res);
int		copy_env(t_data *data, char **env);
void	set_terminal(t_terminal *terminal);
/*
**
** LEXER
**
*/
int		ms_lexer(char *str, t_token **tokens, int *res);
int		tokenize(t_token **tokens, char *str, int *i, int type);
int		lexer_checker(t_token *head);
int		is_delimiter(char *str);
int		is_delimiter_spc(char *str);
int		is_isspace(char c);
int		is_quote(char *str, int *type);
int		is_oper(char c1, char c2, int *type);
int		is_special(char *str, int *type);
char	*copy_chars(char *str, int *i, int n);
char	*copy_word(char *str, int *i);
char	*copy_var(char *str, int *i);
char	*copy_quote(char *str, int *i);
void	add_token(t_token *new, t_token **tokens);
void	check_new(t_token *new);
void	delete_token(t_token **tokens);
t_token	*create_token(int type, char *value);
/*
**
** EXPANSER
**
*/
int		ms_expanser(t_token **tokens, int *res, int exstatus);
int		expanse_exstatus(t_token **tokens, int exstatus);
int		expanse_var(t_token **tokens, int *res);
int		expanse_quote(t_token *tokens, char *str);
int		change_type(t_token **tokens);
int		expanse_wildcard(t_token **wildcard);
void	insert_token(t_token **tokens, t_token *new);
char	*add_space(char *str);
void	delete_token(t_token **tokens);
/*
**
** PARSER
**
*/
int 		ms_parser(t_token *tokens, t_cmdlst **cmds, int *res);
int			cmd_addredir(t_token **token, t_cmd *cmd);
int			is_delim(t_token *token);
int			is_redir(t_token *token);
int			ft_strtoken(char *str);
int			read_file(char *file);
int			read_stdin(char *delimiter, int fd);
int			fork_stdin(char *delimiter);
int			create_file(char *file);
int			append_file(char *file);
int			err_cmd(char *cmd);
void		add_cmdlst(t_cmdlst **lst, t_cmdlst	*new);
void		cmd_setargs(t_token **token, t_cmd *new);
void		set_heredocterm(void);
void		sig_prompt(int signum);
void		sig_eof(char *delimiter);
char		*copy_cmd(t_token **token);
char		*get_cmdpath(char *cmd);
char		*delete_quotes(char *src, char *rest);
t_cmd		*create_cmd(t_token **token);
t_cmd		*init_cmd(void);
t_redir		*create_redir(void);
t_cmdlst	*create_cmdlst(int type, t_cmd *cmd);
/*
**
** EXEC
**
*/
int			ms_execute(t_cmdlst **cmds, char **env);
int			ms_bracket(t_cmdlst **cmds, char **env);
int			ms_wait(t_cmdlst **cmds, int res);
int			exec_cmd(t_cmdlst **cmds, char **env);
int			set_fd(t_cmdlst **cmds);
int			close_fd(t_cmd *cmd);
int			update_fd(t_cmd *cmd);
/*
**
** CLEAN
**
*/
void	clean(t_data *data);
void	free_tokens(t_token **tokens);
void	free_tab(char **table);
/*
**
** UTILS
**
*/
int 	is_alnum(char c);
int		is_alpha(char c);
int		ft_tablen(char **table);
int		ft_isdigit(char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
int		err_msg(int code, char *c, int err);
int		err_bd(int code, int err, char *func, char *arg);
char	*get_next_line(int fd);
char	*err_msg_str(int code, char *str);
char	*ft_itoa(int n);
char	*ft_getenv(char *name);
char	*ft_strchr(char *str, int c);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2, int clean);
char	*ft_strncpy(char *dst, char *src, int n);
char	*ft_strndup(const char *s, int n);
char	**ft_split(char *s, char c);
void	display_tokens(void);
void	display_cmds(void);
void	display_specific_tokens(t_token *head);
/*
**
** BUILTINS
**
*/
int		ms_cd(char *cmd, char **args, char **env);
int		ms_echo(char *cmd, char **args);
int		ms_exit(char *cmd, char **args, char **env);
int		ms_env(char *cmd, char **args, char ** env);
int		ms_export(char *cmd, char **args, char **env);
int		ms_unset(char *cmd, char **args, char **env);
int		ms_pwd(char *cmd, char **args, char **env);
int		display_env(char **env);
int		display_export(char **env);
int		cd_navigate(char *path, char **env, char *pwd);
int		set_pwd(char *newpath, char **env);
int		set_oldpwd(char *newpath, char **env);
int		is_absolute(char *path);
int		nav_backwards(char *path, char **env);
int		nav_oldpwd(char **env);
int		nav_fromhome(char *path, char **env);
int		nav_absolute(char *path, char **env);
int		nav_relative(char *origin, char *path, char **env);
int		nav_back(char *origin, char **env);
int		nav_home(char **env);
int		nav_pwd(char **env);

#endif