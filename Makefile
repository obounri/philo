NAME = philo
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
HEADER = includes/philo.h

UTILS_C = utils/*.c
LIBFT_MAKEFILE_PATH = utils/libft/ 
LIBFT = utils/libft/libft.a

all: $(NAME)

$(NAME): $(HEADER) main.c $(UTILS_C) $(LIBFT)
	$(CC) $(CFLAGS) main.c $(UTILS_C) $(LIBFT) -lpthread -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_MAKEFILE_PATH)

clean:
	make clean -C $(LIBFT_MAKEFILE_PATH)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all
