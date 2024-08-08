NAME := minishell
CC := cc
CFLAGS := -Wall -Werror -Wextra
INCLUDES := -I./include -I./lib/libft/include
LIBFT := lib/libft/libft.a

SRC_DIR := src
INC_DIR := include
BUILD_DIR := bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C lib/libft clean
	rm -rf $(BUILD_DIR)

fclean: clean
	$(MAKE) -C lib/libft fclean
	rm -f $(NAME)

re: fclean all

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: $(LIBFT) all clean fclean re
