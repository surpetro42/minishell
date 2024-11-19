# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 17:20:33 by ayeganya          #+#    #+#              #
#    Updated: 2024/06/06 15:33:44 by ayeganya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compiler CFLAGS
CC = cc
CFLAGS = -Wall -Werror -Wextra -c #-g3 -fsanitize=address

# Archiver and archiver AFLAGS
AA = ar
AFLAGS = rcs

# Header files
H_FILE = libft.h

#Source files
SRC_FILES = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_tolower.c ft_toupper.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_memcmp.c ft_strnstr.c ft_memchr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c \
ft_printf.c ft_printf_helper_functions.c ft_printf_operand_processors.c \
ft_printf_helper_functions2.c ft_printf_helper_functions_bonus.c \
ft_printf_operand_processors2.c get_next_line.c get_next_line_utils.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strcmp.c ft_atof.c

OBJ_FILES = $(SRC_FILES:%.c=%.o)

#Target
NAME  = libft.a

#Default Target
all: $(NAME)

#name Target
$(NAME): $(OBJ_FILES) $(H_FILE)
	$(AA) $(AFLAGS) $@ $^

#object target
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<


#cleaning targets
clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
