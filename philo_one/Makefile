CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
MKDIR = mkdir -p

SRCS =	src/utils.c \
		src/philo.c \
		src/monitor.c \
		src/printing.c \
		src/threads.c \
		src/main.c \

HEADERS = inc/philo_one.h

OBJDIR = objs
OBJS = $(patsubst src/%.c, objs/%.o, $(SRCS))

NAME = philo_one

INCLUDES = -I inc -pthread

objs/%.o: src/%.c $(HEADERS)
	$(MKDIR) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all : $(NAME)


$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS)  -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all