NAME = philo

LIST = free.c ft_atoi.c init.c logs.c main.c \
	   parse.c philosophers_logic.c simulation.c \

OBJ = $(patsubst %.c,%.o, $(LIST))

CC = gcc

CFLAGS = -Wall -Werror -Wextra

HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: clean fclean re
