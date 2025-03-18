NAME = minitalk
SERVER = server
CLIENT = client
CC = cc -Wall -Wextra -Werror

SERVER_SRC	=	mandatory/server.c mandatory/utils.c
CLIENT_SRC	=	mandatory/client.c mandatory/utils.c

S_OBJ = $(SERVER_SRC:.c=.o)
C_OBJ = $(CLIENT_SRC:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(S_OBJ)
	$(CC) -o $(SERVER) $(S_OBJ)

$(CLIENT): $(C_OBJ)
	$(CC) -o $(CLIENT) $(C_OBJ)

%.o: %.c minitalk.h
	$(CC) -c $< -o $@

clean:
	rm -f $(S_OBJ) $(C_OBJ)

fclean: clean
	rm -f $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re