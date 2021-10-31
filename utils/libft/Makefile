# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obounri <obounri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 13:10:19 by obounri           #+#    #+#              #
#    Updated: 2021/10/31 17:35:01 by obounri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# _*_ Makefile _*_

FLAGS = -Wall -Wextra -Werror
HEADER = .
FCTS = ft_atoi.c \
ft_isdigit.c \
ft_putchar_fd.c \
ft_putstr_fd.c
OBJS = $(FCTS:.c=.o)
BONUS_FCTS = ft_lstadd_back_bonus.c \
ft_lstadd_front_bonus.c \
ft_lstclear_bonus.c \
ft_lstdelone_bonus.c \
ft_lstiter_bonus.c \
ft_lstlast_bonus.c \
ft_lstmap_bonus.c \
ft_lstnew_bonus.c \
ft_lstsize_bonus.c
BONUS_OBJS = $(BONUS_FCTS:.c=.o)
NAME = libft.a

all: $(NAME)

bonus: $(BONUS_OBJS) $(OBJS)
	ar rc $(NAME) $(OBJS) $(BONUS_OBJS)
	ranlib $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJS): $(FCTS)
	gcc $(FLAGS) -I $(HEADER) -c $(FCTS)

$(BONUS_OBJS): $(BONUS_FCTS)
	gcc $(FLAGS) -I $(HEADER) -c $(BONUS_FCTS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
