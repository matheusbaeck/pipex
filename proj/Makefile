# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 23:11:40 by mamagalh@st       #+#    #+#              #
#    Updated: 2023/08/04 17:52:58 by mamagalh@st      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

SRCS =  main.c pathing.c pipe.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

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