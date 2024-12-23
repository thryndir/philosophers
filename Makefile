NAME := philosophers
HEADER := -Iinclude
CC := cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
RM := rm -rf

SRC_DIR := src/
SRCS := $(shell find $(SRC_DIR) -name "*.c")

OBJ_DIR := obj/
OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re