# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/15 08:21:19 by alexis            #+#    #+#              #
#    Updated: 2024/10/28 14:44:32 by acoste           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-g -Wall -Werror -Wextra -pthread

NAME		=	philo

SRC_DIR		=	src/

SRC_FILES	=	main.c\
				philosopher.c\
				errors.c\
				utils.c\
				debug.c\
				init.c\
				time.c\
				orders.c

SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ			=	$(SRC:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(SRC_DIR)%.o	:	$(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean		:
				rm -f $(OBJ)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all