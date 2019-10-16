# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/15 14:31:39 by apouchet          #+#    #+#              #
#    Updated: 2019/10/16 13:38:51 by floblanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = #-Wall -Werror -Wextra

INCLUDE = -framework AppKit -framework openGL -lmlx

NAME = fract-ol

SRC = ./main.c ./ft_mandelbrot.c ./key.c ./mouse.c ./ft_zoom.c ./parsing.c

OBJ = $(SRC:.c=.o)

LIB = libftprintf

.PHONY : $(NAME) clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
		make -C $(LIB) -j
		$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME) libftprintf/libprintf.a

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean :
		make -C $(LIB) clean
		rm -rf $(OBJ)

fclean : clean
		make fclean -C $(LIB)
		rm -rf $(NAME)

re : fclean all
