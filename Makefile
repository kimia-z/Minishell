NAME := minishell
CC := cc
CFLAGS := -Wall -Werror
LDFLAG := -lreadline -lncurses
INCLUDES := -I./include -I./lib/libft/include
LIBFT := lib/libft/libft.a

SRC_DIR := src
INC_DIR := include
BUILD_DIR := bin

SRCS = src/expansion/expansion.c src/history/history.c \
		src/lexer/lexer_collect.c src/lexer/lexer_quotes.c \
		src/lexer/lexer_utils.c src/lexer/lexer.c \
		src/lexer/token.c src/lexer/tokenlist.c \
		src/parser/parse_utils.c src/parser/parser.c \
		src/parser/syntax_checker.c src/path/find_path.c \
		src/prompt/cmdline.c src/prompt/env_var.c \
		src/prompt/interactive_shell.c \
		src/prompt/non_interactive_shell.c src/prompt/signals.c \
		src/prompt/termcap.c src/utils/error_handling.c \
		src/utils/test_functions.c src/main.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) 
	$(CC) $(LDFLAG) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C lib/libft

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
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
