CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =	utils.c \
		main.c \

HEADER = philo_one.h \

OBJS = $(SRCS:%.c=%.o)

NAME = philo_one

INCLUDES = -I .

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS)  -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all