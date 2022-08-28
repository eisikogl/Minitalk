SERVER_SRC	=	server.c
OBJS = $(SERVER_SRC:.c=.o)

CLIENT_SRC	=	client.c
OBJC = $(CLIENT_SRC:.c=.o)

RM			=	rm -rf
CC			=	gcc
FLAGS		=	-Wall -Werror -Wextra

all: server client

bonus: server client

server : $(OBJS)
		$(CC) $(FLAGS) $(SERVER_SRC) -o server

client : $(OBJC)
		$(CC) $(FLAGS) $(CLIENT_SRC) -o client

clean:
	$(RM) $(OBJS) $(OBJC)
	
fclean: clean
	$(RM) server client

re : fclean all

.PHONY: all fclean clean re