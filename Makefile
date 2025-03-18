NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_CLIENT = mandatory/client.c mandatory/utils.c
SRC_SERVER = mandatory/server.c mandatory/utils.c

SRC_CLIENT_BONUS = bonus/client_bonus.c bonus/utils_bonus.c
SRC_SERVER_BONUS = bonus/server_bonus.c bonus/utils_bonus.c

C_OBJ = $(SRC_CLIENT:.c=.o)
S_OBJ = $(SRC_SERVER:.c=.o)

C_OBJ_BONUS = $(SRC_CLIENT_BONUS:.c=.o)
S_OBJ_BONUS = $(SRC_SERVER_BONUS:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(C_OBJ)
	$(CC) $(CFLAGS) -o $@ $(C_OBJ)

$(NAME_SERVER): $(S_OBJ)
	$(CC) $(CFLAGS) -o $@ $(S_OBJ)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(C_OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(C_OBJ_BONUS)

$(NAME_SERVER_BONUS): $(S_OBJ_BONUS)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(S_OBJ_BONUS)

%.o: %.c mandatory/minitalk.h bonus/minitalk_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(C_OBJ) $(S_OBJ) $(C_OBJ_BONUS) $(S_OBJ_BONUS)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all

.PHONY: clean