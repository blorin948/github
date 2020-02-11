# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/02/05 20:57:52 by blorin       #+#   ##    ##    #+#        #
#    Updated: 2020/02/11 22:58:22 by blorin      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

MLX = -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit -L mlx/

NAME = Cub3D

SRCS = src/bmp.c\
	src/check_color.c\
	src/check_cub.c\
	src/check_cub2.c\
	src/dda_door.c\
	src/draw.c\
	src/fct.c\
	src/get_next_line.c\
	src/get_next_line_utils.c\
	src/key_gnl.c\
	src/load.c\
	src/main.c\
	src/minimap.c\
	src/move.c\
	src/ray_casting.c\
	src/set_variables.c\
	src/sprite.c\
	src/tab.c\

OBJSRCS = $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

FLAGS = -Wall -Wextra -Werror

CC = gcc

$(NAME) : $(OBJSRCS)
	rm -rf Cub3D
	${CC} $(OBJSRCS) $(MLX) libft.a -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJSRCS)

fclean : clean
	rm -rf $(NAME)
	rm -rf save.bmp

re : fclean all
