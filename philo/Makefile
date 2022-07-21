# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 00:58:37 by keaton            #+#    #+#              #
#    Updated: 2022/07/21 22:31:07 by keaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main.c	destructors.c	actions.c\
				utils.c	initiations.c
OBJ			=	$(SRC:.c=.o)
HEADER		=	philo.h
CC_FLAGS	=	-pthread -Wall -Werror -Wextra #-fsanitize=thread -g
NAME		=	philo
RM			=	rm -rf

.PHONY : all re clean fclean

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CC_FLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CC_FLAGS) -c $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
