CC = gcc
CFLAGS = -Wall -Wextra -Werror
MKDIR = mkdir -p

SRCS =	src/utils.c \
		src/philo.c \
		src/monitor.c \
		src/printing.c \
		src/processes.c \
		src/main.c \

HEADERS = philo_three.h

OBJDIR = objs
OBJS = $(patsubst src/%.c, objs/%.o, $(SRCS))

NAME = philo_three

INCLUDES = -I inc -pthread

objs/%.o: src/%.c
	$(MKDIR) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

all : $(NAME)


$(NAME) : $(OBJS) $(HEADER) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS)  -o $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all