NAME = minishell

READLINE = readline
CC = cc

INC_DIRS = -I./includes -I./$(LIBS_DIR)/$(READLINE)/include
CFLAGS = -Wall -Wextra -Werror $(INC_DIRS) -g3 -fsanitize=address
LIBS_DIR = libraries
READLINE_LIB_PATH = $(LIBS_DIR)/readline/lib

HEADERS = 	includes/minishell.h \

SRCS_DIR = src/

OBJS_DIR = objects/

SRCS_NAME =		minishell.c \
				functions/ctrl_d.c \
				functions/dollar.c \
				functions/cd.c \
				functions/pwd.c \
				functions/ft_execve.c \
				functions/echo.c \
				functions/env.c \
				functions_utils/duplicate_env.c \
				functions_utils/cd_utils.c \
				functions_utils/utils_dollar.c \
				jamanakavor/jamanakavor.c \
				utils/utils.c

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

all: $(LIBS_DIR)/$(READLINE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -l$(READLINE) -L$(READLINE_LIB_PATH)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/functions
	@mkdir -p $(OBJS_DIR)/jamanakavor
	@mkdir -p $(OBJS_DIR)/functions_utils
	$(CC) $(CFLAGS) -c $< -o $@ 

$(LIBS_DIR)/$(READLINE):
	./$(LIBS_DIR)/config_readline readline

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	rm -rf $(LIBS_DIR)/$(READLINE)
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBS_DIR)/readline-8.2

re: fclean all

.PHONY: all clean fclean re