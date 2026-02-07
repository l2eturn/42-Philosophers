NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
RM			= rm -f

SRCS		= main.c \
			  main_helper.c \
			  init.c \
			  routines.c \
			  action.c \
			  helper.c \
			  utils.c

OBJS		= $(SRCS:.c=.o)

HEADER		= philosopher.h

# ===== RULES =====

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
