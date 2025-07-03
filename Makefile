SOURCES = server.c client.c utils.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: server client

bonus: server client

server: server.o utils.o
	$(CC) -o $@ $^

client: client.o utils.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS) utils.o
fclean: clean
	rm -f server client

re: fclean all

.PHONY: all bonus clean fclean re
