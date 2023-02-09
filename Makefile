# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jperales <jperales@student.42urduli>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/05 17:49:36 by jperales          #+#    #+#              #
#    Updated: 2022/10/26 17:29:22 by jperales         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

RM = rm -f

CC = gcc

CFLAGS = -Wall -Werror -Wextra -pthread #-g3 -fsanitize=address

SRC = main.c\
	  utils.c\
	  time.c\
	  begin.c\
	  actions.c\

OBJS = $(SRC:.c=.o)

.c.o: $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

re: fclean all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

.PHONY: all re clean fclean
