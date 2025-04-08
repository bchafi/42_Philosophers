NAME = philo
CC = cc -Wall -Wextra -Werror #-fsanitize=address -g

SOURCES = \
	philo.c \
	utils/ft_isdigit.c utils/ft_isspace.c utils/ft_puterror_fd.c utils/ft_split.c \
	utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strdup.c utils/ft_substr.c \
	utils/ft_printf.c utils/ft_printf_utils.c utils/ft_atoi.c \
	Mandatory/parcing.c Mandatory/initialize.c\

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME) -lpthread

 %.c : %.o #philo.h
	$(CC) $^ -c $<

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: all clean