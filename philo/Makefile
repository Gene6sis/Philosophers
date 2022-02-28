# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adben-mc <adben-mc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 00:45:16 by adben-mc          #+#    #+#              #
#    Updated: 2022/02/28 01:38:44 by adben-mc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR		=	srcs/

SRCS			=	$(SRCS_DIR)main.c		\
					$(SRCS_DIR)ft_error.c	\
					$(SRCS_DIR)ft_check.c	\
					$(SRCS_DIR)ft_utils.c	\
					$(SRCS_DIR)ft_routine.c	\
					$(SRCS_DIR)ft_thread.c
					
OBJS			= 	${SRCS:.c=.o}

NAME			= 	philo

INC_DIR			=	./includes/.
CC				=	gcc -I$(INC_DIR)
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror -pthread #-g3 -fsanitize=address

all:		$(NAME)

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			$(CC)  $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
