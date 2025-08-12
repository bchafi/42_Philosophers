# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 22:55:10 by bchafi            #+#    #+#              #
#    Updated: 2025/08/12 15:32:03 by bchafi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
Green = \033[0;32m
Reset = \033[0m
CC = cc -Wall -Wextra -Werror
SOURCES = \
	philo.c \
	utils/ft_split.c \
	utils/ft_lib.c \
	utils/ft_function.c \
	utils/parcing.c \
	utils/initialize.c \
	utils/sleeper.c \
	utils/map_routine.c \
	utils/routines.c \

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(NAME)
	@echo "$(Green)--// Make All Is Done!! //--$(Reset)"

%.o: %.c philo.h
	@$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "$(Green)--// Make Clean Is Done!! //--$(Reset)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(Green)--// Make Fclean Is Done!! //--$(Reset)"

re: fclean all