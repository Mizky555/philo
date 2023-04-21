SRCS			= check_file.c philo_util.c philo.c initialize.c status.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -rf
CFLAGS			= -Wall -Wextra -Werror -pthread
CFLAGS			= -pthread

NAME			= philo

all:			$(NAME)

$(NAME):		$(OBJS)
					$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


clean:
					$(RM) $(OBJS)

fclean:			clean
					$(RM) $(NAME) $(NAME).dSYM

re:				fclean $(NAME)


.PHONY:			all clean fclean re
