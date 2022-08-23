# Colors
RED			= "\033[1;31m"
GREEN		= "\033[1;32m"
RESET		= "\033[m"

# Compilation flags
ifeq ($(DMEM),1)
MEM 		= -fsanitize=address
endif

ifeq ($(DTHREAD),1)
MEM 		= -fsanitize=thread
endif

# Variables
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -g
CC			= cc
FLAGS		= -lreadline

OBJ_DIR		= objs/
SRC_DIR		= src/
INC_DIR		= inc/

SRC_FILES	=	minishell.c \
				init/init.c \
				lexer/lexer.c lexer/tokenize.c lexer/copy.c lexer/utils.c

OBJS		= $(addprefix ${OBJ_DIR}, ${SRC_FILES:.c=.o})
INC			= -I./$(INC_DIR)

# Rules
all : $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p ${@D}
	$(CC) $(CFLAGS) $(MEM) $(INC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(FLAGS) $(MEM) $(INC) $(OBJS) -o $@
	@echo -n "Compiling minishell"
	@echo $(GREEN)"\tOK"$(RESET)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
	make all

.PHONY : all clean fclean re