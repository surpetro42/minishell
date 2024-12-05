# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/16 12:29:06 by ayeganya          #+#    #+#              #
#    Updated: 2024/12/03 22:56:02 by surpetro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler and compiler CFLAGS
CC = cc
CFLAGS = -Wall -Werror -Wextra  #-fsanitize=address #-g -O0
# RLLIBFLAGS = -Ireadline/include -Lreadline/lib -lreadline -lhistory

# Header files
H_FILE = minishel.h

#Readline
READLINE_DIR = readline-8.2
RL = readline
lib_path := "$(shell pwd)/readline"

#Source files
SRC_FILES = init.c builtins_minishel/src/functions/dollar.c \
			builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_0.c \
			builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_1.c \
			builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_2.c \
			builtins_minishel/src/functions_utils/utils_dollar/dollar_utils_3.c \
			builtins_minishel/src/functions_utils/utils_export/export_utils_0.c \
			builtins_minishel/src/functions_utils/utils_export/export_utils_1.c \
			builtins_minishel/src/functions_utils/utils_export/export_utils_2.c \
			builtins_minishel/src/functions_utils/utils_export/export_utils_3.c \
			builtins_minishel/src/functions_utils/cd_utils.c \
			builtins_minishel/src/functions/echo.c \
			builtins_minishel/src/functions/cd.c \
			builtins_minishel/src/functions/export.c \
			builtins_minishel/src/functions/env.c \
			builtins_minishel/src/functions/unset.c \
			builtins_minishel/src/functions/pwd.c \
			builtins_minishel/src/functions/exit.c \
			builtins_minishel/src/env/duplicate_env.c \
			builtins_minishel/src/free_builtins/free_dollar.c \
			builtins_minishel/src/free_builtins/free_exp_env_list.c \
			builtins_minishel/src/free_builtins/free_export.c
			
#B_SRC_FILES =

OBJ_FILES = $(SRC_FILES:%.c=%.o)

#Libft
LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a

#Target
NAME  = minishell
BONUS = minishell

all: $(LIBFT_A) $(RL) $(NAME)

$(NAME): $(OBJ_FILES) $(H_FILE)
	$(CC) $(CFLAGS) -Lreadline/lib -lreadline -lhistory $(OBJ_FILES) $(LIBFT_A) -o $@

#Object target
%.o: %.c Makefile $(H_FILE)
	$(CC) $(CFLAGS) -Ireadline/include -c -o $@ $<

#Readline libraries compilation
$(RL):
	mkdir readline
	cd $(READLINE_DIR) && ./configure --prefix=$(lib_path) && make && make install

#Libft target
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)


bonus: $(LIBFT_A) $(NAME)

#cleaning targets
clean:
	rm -f $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(READLINE_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(READLINE_DIR) distclean
	rm -rf readline

re: fclean all

lclean:
	rm -f $(OBJ_FILES)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(READLINE_DIR) clean


rf: lclean $(NAME)

.PHONY: all clean fclean re rf lclean
