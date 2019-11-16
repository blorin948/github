# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: blorin <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/11/16 14:41:03 by blorin       #+#   ##    ##    #+#        #
#    Updated: 2019/11/16 14:44:51 by blorin      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRC = convert_c_s_d.c\
	  ft_printf.c\
	  ftc1.c\

OBJS = ${SRC:.c=.o}

OBJBS = ${SRCB:.c=.o} ${SRC:.c=.o}

NAME = libftprintf.a

RM = rm -f

CC = gcc

HEADERS = ft_printf.h

CFLAGS = -o -Wall -Wextra -Werror

all:	${NAME}

$(OBJS): ${HEADERS}

$(OBJBS): ${HEADERS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}

bonus:		${OBJS} ${OBJBS}
	ar rc ${NAME} ${OBJBS}
	ranlib ${NAME}

fclean:		clean
	${RM} ${NAME}

clean:
	${RM} *.o

re: fclean all

.PHONY:		all clean fclean re
