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

FLAGS = #-Wall -Werror -Wextra

INCLUDE = -framework AppKit -framework openGL -lmlx

NAME = fract-ol

SRC = ./main.c ./ft_mandelbrot.c ./key.c ./mouse.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
		gcc $(FLAGS) $(INCLUDE) $(OBJ) -o $(NAME)

clean :
		rm -rf $(OBJ)

fclean : clean
		rm -rf $(NAME)

re : fclean all

#‘sdl-config --libs‘ -lSDL_ttf
# -L ~/.brew/lib -lSDL2 -L ~/.brew/lib -libSDL2_ttf -I ~/.brew/include -framework Cocoa
# brew install sdl2_ttf
