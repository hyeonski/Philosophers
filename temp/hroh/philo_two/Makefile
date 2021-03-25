NAME = philo_two
CC = gcc #-g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c util.c action.c exit.c messages.c init.c util_str.c util_num.c 
OBJS = $(SRCS:.c=.o)
LIBS = -lpthread

all: $(NAME)

.c.o: 
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^ ${LIBS}

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re