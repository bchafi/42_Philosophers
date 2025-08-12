# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/10 22:55:10 by bchafi            #+#    #+#              #
#    Updated: 2025/08/11 18:37:55 by bchafi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
Green = \033[0;32m
Reset = \033[0m
CC = cc -Wall -Wextra -Werror -fsanitize=thread
SOURCES = \
	philo.c \
	utils/ft_isdigit.c \
	utils/ft_isspace.c \
	utils/ft_puterror_fd.c \
	utils/ft_split.c \
	utils/ft_strjoin.c \
	utils/ft_strlen.c \
	utils/ft_strdup.c \
	utils/ft_substr.c \
	utils/ft_atoi.c \
	utils/ft_memset.c \
	utils/ft_strncmp.c \
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

%.o: %.c philo.c
	@$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "$(Green)--// Make Clean Is Done!! //--$(Reset)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(Green)--// Make Fclean Is Done!! //--$(Reset)"

re: fclean all