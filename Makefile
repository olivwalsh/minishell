# Colors
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
RESET		= "\033[m"

# Variables
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror
CC			= cc
FLAGS		= -lreadline

OBJ_DIR		= objs/
SRC_DIR		= src/
INC_DIR		= inc/

SRC_FILES	=	minishell.c \
				init/init.c init/env.c init/terminal.c \
				lexer/lexer.c lexer/tokenize.c lexer/copy.c lexer/delimiter.c lexer/utils_1.c lexer/utils_2.c lexer/checker.c lexer/bracket.c \
				expanser/expanser.c expanser/var.c expanser/quote.c expanser/tilde.c expanser/exstatus.c expanser/insert.c expanser/wildcards.c expanser/utils.c \
				parser/parser.c parser/init.c parser/cmd.c parser/delete.c parser/redir.c parser/utils.c parser/path.c parser/file.c parser/args.c \
				parser/heredoc/heredoc.c parser/heredoc/signals.c \
				exec/execute.c exec/bracket.c exec/process.c exec/wait.c exec/fd.c \
				utils/is.c utils/error.c utils/utils.c utils/ft_str_1.c utils/ft_str_2.c utils/split.c utils/get_next_line.c utils/convert.c utils/mem.c \
				builtins/builtins.c builtins/ms_exit.c builtins/ms_env.c builtins/ms_echo.c builtins/ms_export.c builtins/ms_pwd.c builtins/ms_unset.c builtins/display.c \
				builtins/ms_cd/ms_cd.c builtins/ms_cd/navigate_1.c builtins/ms_cd/navigate_2.c builtins/ms_cd/navigate_3.c builtins/ms_cd/utils.c \
				clean/clean.c 

OBJS		= $(addprefix ${OBJ_DIR}, ${SRC_FILES:.c=.o})
INC			= -I./$(INC_DIR)

# Rules
all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p ${@D}
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) -o  $@ $(FLAGS)
	@echo -n "Compiling minishell"
	@echo $(GREEN)"\tOK"$(RESET)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
	make all

.PHONY : all clean fclean re