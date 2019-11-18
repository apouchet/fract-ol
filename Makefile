# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 10:08:34 by maginist          #+#    #+#              #
#    Updated: 2019/11/18 15:22:25 by floblanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
APP_NAME = fract-ol
FRAMEWORK = /System/Library/Frameworks/OpenGL.framework /System/Library/Frameworks/AppKit.framework
SHADER = ./shader/
HUD = ./hud/
SRC_NAME =	main.c 				\
			ft_mandelbrot.c		\
			ft_zoom.c			\
			key.c				\
			mouse.c 			\
			parsing.c			\
			opengl.c			\
			file.c				\
			ft_shader_opengl.c	\
			ft_hud.c 			\
			ft_screenshot.c		\
			ft_control_gl.c		\
			ft_opti.c			\
			ft_other_fract.c	\
			ft_create_fdf.c		\
			init.c

SRC_PATH = ./src/

OBJ_PATH = ./obj/

INC_PATH = ./include/
INC_BREW = ~/.brew/include/
INC_NAME =	fract.h


LIBFT				=	./libftprintf/
LIBFTA				=	libprintf.a
LIBFTINCLUDES		=	./libftprintf/include/
FRACT_FLAGS = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
#FRACT_FLAGS = -I /usr/local/include -L /usr/local/lib/ mlx/libmlx.a -framework OpenGL -framework AppKit
OPENGL_FLAGS = -L ~/.brew/lib -lglfw -lglew
#OPENGL_FLAGS = -lglew -lglfw 

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
		@echo "\n"
		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
		@echo "|    COMPILING FRACT-OL  |"
		@echo "$(_RED)|_-_-_-_-_-_-_-_-_-_-_-_-|$(_END)"
		@echo "\n"
		@$(CC) $(FRACT_FLAGS) $(OPENGL_FLAGS) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)/$(LIBFTA)
		@echo "$(_GREEN)[ FRACT-OL DONE ]$(_END)"

clean :
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)
	@echo "$(_BLUE)======< CLEAN PROJECT & LIBPRINTF DONE >======$(_END)"
	@rm -f ./libprintf.a

fclean : clean app_clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo "$(_BLUE)======< FCLEAN PROJECT & LIBPRINTF DONE >======$(_END)"

re : fclean all

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -Wno-deprecated-declarations -I $(LIBFTINCLUDES) -I $(INC_PATH) -I $(INC_BREW) -c $< -o $@

app : all
	@mkdir -p "./$(NAME).app"/Contents/{MacOS,Resources}
	@cp -R $(HUD) "./$(NAME).app/Contents/Resources/$(HUD)"
	@cp -R $(SHADER) "./$(NAME).app/Contents/Resources/$(SHADER)"
	@cp app/fract.icns	"./$(NAME).app/Contents/Resources/"
	@cp app/PkgInfo	"./$(NAME).app/Contents/"
	@cp app/Info.plist "./$(NAME).app/Contents/"
	@cp $(NAME) "./$(NAME).app/Contents/MacOS/$(NAME)"
	@echo "$(_GREEN)[ APP DONE ]$(_END)"

app_clean :
	@rm -rf "./$(NAME).app/"
	@echo "$(_BLUE)======< CLEAN APP DONE >======$(_END)"

app_re : app_clean app

