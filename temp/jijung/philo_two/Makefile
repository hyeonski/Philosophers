NAME	=	philo_two

SRCS	=	srcs/utils.c			\
			srcs/argu_check.c		\
			srcs/main.c				\
			srcs/behavior.c			\
			srcs/message.c			\
			srcs/clean.c			\
			srcs/init.c				\
			srcs/check_must_eat.c	\

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

FLAGS	=	-lpthread

#.c.o:
#		$(CC) $(CFALGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFALGS) -o $(NAME) $(FLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
