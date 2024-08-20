# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabansac <sabansac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 22:05:54 by sabansac          #+#    #+#              #
#    Updated: 2024/08/20 05:47:35 by sabansac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME := pipex
CC := gcc
SRCDIR := src/
BNSDIR := src/bns/
LIBFTDIR := includes/libft/
CFLAGS := -Wall -Wextra -Werror
INCLFLAGS := -I$(SRCDIR) -I$(LIBFTDIR)
LDFLAGS := -L$(LIBFTDIR) -lft

SRC_FILES := main.c pipex.c utils.c
SRC := $(addprefix $(SRCDIR), $(SRC_FILES))
OBJ := $(SRC:.c=.o)

BNS_FILES := main_bonus.c pipex_bonus.c here_doc_bonus.c utils_bonus.c
BNS := $(addprefix $(BNSDIR), $(BNS_FILES))
BNS_OBJ := $(BNS:.c=.o)

HEADER := $(SRCDIR)pipex.h
BNS_HEADER := $(BNSDIR)pipex_bonus.h

LIBFT := $(LIBFTDIR)libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

bonus: $(LIBFT) $(BNS_OBJ)
	$(CC) $(CFLAGS) $(BNS_OBJ) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(SRCDIR)%.o: $(SRCDIR)%.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLFLAGS) -c $< -o $@

$(BNSDIR)%_bonus.o: $(BNSDIR)%_bonus.c $(BNS_HEADER)
	$(CC) $(CFLAGS) $(INCLFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	rm -f $(OBJ) $(BNS_OBJ)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re