# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 20:19:40 by mamagalh@st       #+#    #+#              #
#    Updated: 2023/11/07 01:02:44 by mamagalh@st      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc

SRCS = main.c pathing.c pipe.c utils.c heredoc.c

SRCS_BONUS = main_bonus.c pathing.c pipe.c utils.c heredoc.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address #-g3

ifeq ($(MAKECMDGOALS),bonus)
  OBJS = ${OBJS_BONUS}
endif

all: $(NAME)

$(NAME): libft/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

libft/libft.a:
	@make -C libft

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME) *.o

ffclean: fclean
	@make fclean -C libft

re: fclean all

test:
	./pipex Makefile cat cat out

.PHONY: bonus

bonus: all
