SRCS			= check_file.c philo_util.c philo.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc -g
RM				= rm -f
# CFLAGS			= -Wall -Wextra -Werror -pthread
CFLAGS			= -pthread

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
					$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


clean:
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME)

re:				fclean $(NAME)


.PHONY:			all clean fclean re bonus
