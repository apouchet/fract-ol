# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apouchet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:31:39 by apouchet          #+#    #+#              #
#    Updated: 2019/10/15 14:31:40 by apouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = #-Wall -Werror -Wextra

INCLUDE = -framework AppKit -framework openGL -lmlx

NAME = fract-ol

SRC = ./main.c ./ft_mandelbrot.c ./key.c ./mouse.c ./ft_zoom.c

OBJ = $(SRC:.c=.o)

.PHONY : $(NAME) clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(NAME)

re : fclean all
