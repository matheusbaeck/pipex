# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: math42 <math42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 23:11:40 by mamagalh@st       #+#    #+#              #
#    Updated: 2023/07/06 00:18:01 by math42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

SRCS =  main.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)
	@make clean

libft/libft.a:
	@make -C libft

clean: 
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

test:
	./pipex f_infile ls ls f_outfile