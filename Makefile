NAME := minishell
CC := cc
CFLAGS := -Wall -Werror -Wextra -g
LIBFT_INCLUDES := -I./lib/libft/include
MINISHELL_INCLUDES := -I./include
INCLUDES = $(LIBFT_INCLUDES) $(MINISHELL_INCLUDES) 
BUILD_DIR := bin
SRC_DIR := src
INC_DIR := include
LIBFT := lib/libft/libft.a
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

clean:
	$(MAKE) -C lib/libft clean
	rm -rf $(BUILD_DIR)

fclean: clean
	$(MAKE) -C lib/libft fclean
	rm -f $(NAME).a

re: fclean all

test:
	valgrind --leak-check=full --show-leak-kinds=all

.PHONY: $(LIBFT) all clean fclean re
