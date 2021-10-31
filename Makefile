NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = includes/philo.h

UTILS = utils/*.c

all: $(NAME)

$(NAME): $(HEADER) main.c $(UTILS)
	$(CC) $(CFLAGS) main.c $(UTILS) -lpthread -o $(NAME)


clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all
