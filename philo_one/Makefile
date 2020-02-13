CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c \
		utils.c \

HEADER = philo_one.c \

OBJS = $(SRCS:%.c=%.o)

NAME = philo_one

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I. -o $(NAME)

clean:
	$(RM) $(OBJS)

flcean: clean
	$(RM) $(NAME)