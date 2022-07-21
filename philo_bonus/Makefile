# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/16 00:58:37 by keaton            #+#    #+#              #
#    Updated: 2022/07/21 17:33:27 by keaton           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			=	main_bonus.c	destructors_bonus.c	actions_bonus.c\
				utils_bonus.c	initiations_bonus.c	libpart_bonus.c
OBJ			=	$(SRC:.c=.o)
HEADER		=	philo_bonus.h
CC_FLAGS	=	-pthread -Wall -Werror -Wextra #-fsanitize=thread -g
NAME		=	philo_bonus
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
