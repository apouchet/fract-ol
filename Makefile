# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 10:08:34 by maginist          #+#    #+#              #
#    Updated: 2019/10/21 13:16:39 by floblanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_NAME =	main.c 			\
			ft_mandelbrot.c	\
			ft_zoom.c		\
			key.c			\
			mouse.c 		\
			parsing.c		\
			opengl.c		\
			file.c			\
			ft_control_gl.c	\
			ft_shader_opengl.c\
			ft_hud.c

SRC_PATH = ./src/

OBJ_PATH = ./obj/

INC_PATH = ./include/
INC_BREW = ~/.brew/include/
INC_NAME =	fract.h


LIBFT				=	./libftprintf/
LIBFTA				=	libprintf.a
LIBFTINCLUDES		=	./libftprintf/include/

FRACT_FLAGS = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
# FRACT_FLAGS = -I /usr/local/include -L /usr/local/lib/ mlx/libmlx.a -framework OpenGL -framework AppKit
OPENGL_FLAGS = -L ~/.brew/lib -lglfw -lglew
CC = gcc

CFLAGS = -Wall -Werror -Wextra

# Colors
CK = $'\033[30m$'
_RED = $'\033[31m$'
_GREEN = $'\033[32m$'
_YELLOW = $'\033[33m$'
_BLUE = $'\033[34m$'
_PURPLE = $'\033[35m$'
_CYAN = $'\033[36m$'
_GREY = $'\033[37m$'
_END=$'\033[0m$'


INC	= $(addprefix $(INC_PATH), $(INC_NAME))
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

.PHONY :	all clean fclean re

all: $(NAME)

$(LIBFT)/$(LIBFTA):
	@make -C $(LIBFT) -j 100
	@echo "$(_GREEN)[ LIBPRINTF DONE ]$(_END)"

$(NAME) : $(LIBFT)/$(LIBFTA) $(OBJ)
# 		@echo "\n"
# 		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
# 		@echo "|    COMPILING FRACT-OL  |"
# 		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
# 		@echo "\n"
		$(CC) $(FRACT_FLAGS) $(OPENGL_FLAGS) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)/$(LIBFTA)
# 		@echo "$(_GREEN)[ FRACT-OL DONE ]$(_END)"

clean :
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)
	@echo "$(_BLUE)======< CLEAN PROJECT & LIBPRINTF DONE >======$(_END)"
	@rm -f ./libprintf.a

fclean : clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo "$(_BLUE)======< FCLEAN PROJECT & LIBPRINTF DONE >======$(_END)"

re : fclean all

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(LIBFTINCLUDES) -I $(INC_PATH) -I $(INC_BREW) -c $< -o $@

# opengl compilation:
# gcc -I ~/.brew/include/ -L/Users/apouchet/.brew/lib -lglfw -lglew -framework AppKit -framework OpenGl opengl.c ft_shader_opengl.c file.c ft_control_gl.c
