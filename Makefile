NAME = philo
CC = cc -Wall -Wextra -Werror -fsanitize=address -g

SOURCES = \
	philo.c \
	utils/ft_isdigit.c utils/ft_isspace.c utils/ft_puterror_fd.c utils/ft_split.c \
	utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strdup.c utils/ft_substr.c \

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

%.o : %.c philo.h
	$(CC) $^ -c $<

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all