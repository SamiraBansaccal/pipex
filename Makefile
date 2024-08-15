# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbansacc <sbansacc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 22:05:54 by sabansac          #+#    #+#              #
#    Updated: 2024/08/13 22:57:25 by sbansacc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
SRCDIR = src/
INCLDIR = includes/libft
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LFLAGS = -I$(INCLDIR) -L$(INCLDIR) -lft

SRC_FILES = main.c \
	pipex.c \
	
BNS_FILES = main_bonus.c \
	pipex_bonus.c \
	here_doc_bonus.c \

SRC = $(addprefix $(SRCDIR), $(SRC_FILES))
BNS = $(addprefix $(SRCDIR), $(BNS_FILES))

OBJ = $(SRC:.c=.o)
BNS_OBJ = $(BNS:.c=.o)
ALL_OBJ = $(OBJ) $(BNS_OBJ)

all: libft $(NAME)

libft:
	$(MAKE) -C $(INCLDIR)
$(SRCDIR)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $@
bonus: libft $(BNS_OBJ)
	$(CC) $(CFLAGS) $(BNS_OBJ) $(LFLAGS) -o $(NAME)
clean:
	rm -f $(ALL_OBJ)
	$(MAKE) -C $(INCLDIR) clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(INCLDIR) fclean
re: fclean all

.PHONY: all clean fclean re