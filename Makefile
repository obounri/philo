NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = includes/philo.h

UTILS = utils/init_store.c \
utils/routine.c \
utils/utils.c

all: $(NAME)

$(NAME): $(HEADER) main.c $(UTILS)
	$(CC) $(CFLAGS) main.c $(UTILS) -lpthread -o $(NAME)


clean:
	rm -f $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all
