SRCS	=	main.c monitor.c utils.c
OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -I.
CC		= gcc
NAME	= philosopher
all		: $(NAME) clean
$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean	:
	rm -f $(OBJS)
fclean	: clean
	rm -f $(NAME)
re	: fclean all
