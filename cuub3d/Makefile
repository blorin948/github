# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/02/05 20:57:52 by blorin       #+#   ##    ##    #+#        #
#    Updated: 2020/02/08 20:22:47 by blorin      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

MLX = -lmlx -lm -framework OpenGL -framework AppKit
#MLX = -I /usr/include -g -L /usr/lib -lX11 -lmlx -lXext -lm -fsanitize=address

NAME = cub3D

SRCS = bmp.c\
	check_color.c\
	check_cub.c\
	check_cub2.c\
	dda_door.c\
	draw.c\
	fct.c\
	get_next_line.c\
	get_next_line_utils.c\
	key_gnl.c\
	load.c\
	main.c\
	minimap.c\
	move.c\
	ray_casting.c\
	set_variables.c\
	sprite.c\
	tab.c\

OBJSRCS = $(SRCS:.c=.o) 

$(NAME) : $(OBJSRCS)
	rm -rf Cub3D
	$(MAKE) bonus -C ./libft
	gcc $(OBJSRCS) $(MLX) ./libft/libft.a -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJSRCS)
	$(MAKE) clean -C ./libft

fclean : clean
	$(MAKE) fclean -C ./libft
	rm -rf $(NAME)
	rm -rf cub3d.bmp

re : fclean all

bonus : $(NAME)