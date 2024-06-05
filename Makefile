NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra - Werror -g
HEADER = -Include

FILES = exec init verif utils main
SRC_DIR = src/
OBJ_DIR = obj/

SRCS = $(addprefix $(SRC_DIR), addsuffix .c $(FILES))
OBJS = $(addprefix $(OBJ_DIR), addsuffix .o $(FILES))

all: $(NAME)

$(NAME): $(OBJS) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re