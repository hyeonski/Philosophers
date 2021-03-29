NAME	=	philo_one
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

INCS	=	-I .
SRCS	=	main.c routine.c monitor.c utils.c
OBJS	=	$(SRCS:%.c=%.o)

%.o:%.c
			$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) $(INCS) -o $(NAME)
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
