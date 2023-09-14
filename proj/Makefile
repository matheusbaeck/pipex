# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: math42 <math42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 23:11:40 by mamagalh@st       #+#    #+#              #
#    Updated: 2023/09/15 00:37:54 by math42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

SRCS =  main.c pathing.c pipe.c utils.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -fsanitize=address #-g3

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

libft/libft.a:
	@make -C libft

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

ffclean: fclean
	@make fclean -C libft

re: fclean all

test:
	./pipex here_doc a cat cat out
