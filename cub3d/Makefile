# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: blorin <blorin@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2020/02/05 20:57:52 by blorin       #+#   ##    ##    #+#        #
#    Updated: 2020/02/12 19:22:05 by blorin      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRC = src/bmp.c\
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

OBJS = ${SRC:.c=.o}

OBJBS = ${SRCB:.c=.o} ${SRC:.c=.o}

NAME = Cub3d

RM = rm -f

CC = gcc

HEADERS = cub3d.h get_next_line.h

CFLAGS = -o -Wall -Wextra -Werror

all:	${NAME}

$(OBJS): ${HEADERS}

$(OBJBS): ${HEADERS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	gcc ${NAME} ${OBJS}

fclean:		clean
	${RM} ${NAME}

clean:
	${RM} *.o

re: fclean all

.PHONY:		all clean fclean re