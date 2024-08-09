# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 22:05:54 by sabansac          #+#    #+#              #
#    Updated: 2024/08/02 06:01:49 by sabansac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
SRCDIR = src/
INCLDIR = includes/libft
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
LFLAGS = -I$(INCLDIR) -L$(INCLDIR) -lft

SRC_FILES = main.c \
	pipex.c \

SRC = $(addprefix $(SRCDIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

all: libft $(NAME)

libft: 
	$(MAKE) -C $(INCLDIR)

$(SRCDIR)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $@

clean:
	rm -f $(SRCDIR)*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re