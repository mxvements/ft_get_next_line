CC=gcc

CFLAGS=-Wall -Wextra -Werror -g3

NAME=get_next_line.a

MY_SOURCES=get_next_line.c

MY_OBJECTS=$(MY_SOURCES%.c=%.o)

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	ar -crs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(MY_OBJECTS)

fclean: clean
	rm -rf $(NAME)

norminette:
	norminette $(MY_SOURCES)

re: fclean all

