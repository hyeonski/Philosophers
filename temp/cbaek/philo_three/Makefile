# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 10:03:34 by cbaek             #+#    #+#              #
#    Updated: 2021/03/25 10:48:24 by cbaek            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_three
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LEAKS	=	-g -fsanitize=address -fsanitize=undefined -std=c99
RM		=	rm -f

INCS	=	-I ./include
SRCS	=	main.c exec_act.c philo_monitor.c process_monitor.c util.c
OBJS	=	$(SRCS:%.c=%.o)

%.o:%.c
			$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all:		$(NAME)
$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $(NAME)
debug:		fclean $(OBJS)
			$(CC) $(CFLAGS) $(LEAKS) $(OBJS) $(INCS) -o $(NAME)
clean:
			$(RM) $(OBJS)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all
.PHONY:		all debug clean fclean re
