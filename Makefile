NAME := minishell
CC := cc
CFLAGS := -Wall -Werror
LDFLAG := -lreadline -lncurses
INCLUDES := -I./include -I./lib/libft/include
LIBFT := lib/libft/libft.a

SRC_DIR := src
INC_DIR := include
BUILD_DIR := bin

SRCS = src/expansion/expansion.c src/setup/history.c \
		src/lexer/lexer_collect.c src/lexer/lexer_quotes.c \
		src/lexer/lexer_utils.c src/lexer/lexer.c \
		src/lexer/token.c src/lexer/tokenlist.c \
		src/parser/parse_utils.c src/parser/parser.c \
		src/parser/syntax_checker.c src/execution/find_path.c \
		src/setup/cmdline.c src/setup/env_var.c src/setup/signals.c \
		src/utils/error_handling.c src/utils/test_functions.c \
		src/main.c src/setup/prompt.c src/parser/heredoc.c \
		src/execution/builtins/cd.c src/execution/builtins/echo.c \
		src/execution/builtins/env.c src/execution/builtins/exit.c \
		src/execution/builtins/export.c src/execution/builtins/pwd.c \
		src/execution/builtins/unset.c src/execution/execute.c \
		src/execution/utils.c src/execution/pipe.c

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

#-g -fsanitize=address