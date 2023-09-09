# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 23:11:40 by mamagalh@st       #+#    #+#              #
#    Updated: 2023/09/09 17:46:55 by mamagalh@st      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

SRCS =  main.c pathing.c pipe.c utils.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address #-g3

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

ffclean: fclean
	@make fclean -C libft

re: fclean all

test:
	bash /Users/mamagalh/pipex/test/test.sh