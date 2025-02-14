# Project name
NAME = minishell
OUT_DIR = output

# AST
AST_DIR = src/parsing/ast
MINI_AST_SRC = $(AST_DIR)/ast_create.c $(AST_DIR)/ast_create_pipe.c $(AST_DIR)/ast_create_redirect_in.c $(AST_DIR)/ast_create_command.c $(AST_DIR)/ast_create_redirect.c $(AST_DIR)/ast_create_redirect_out.c $(AST_DIR)/ast_delete.c $(AST_DIR)/ast_utils.c

# Builtins
BUILTINS_DIR = src/builtins
MINI_BUILTINS_SRC = $(BUILTINS_DIR)/builtin_pwd.c $(BUILTINS_DIR)/builtin_env.c $(BUILTINS_DIR)/builtin_unset.c $(BUILTINS_DIR)/builtin_set_private.c $(BUILTINS_DIR)/builtin_export.c $(BUILTINS_DIR)/builtin_export_ext.c $(BUILTINS_DIR)/builtin_exit.c $(BUILTINS_DIR)/builtin_echo.c

# TOKENS
TOKENS_DIR = src/parsing/tokens
MINI_TOKENS_SRC = $(TOKENS_DIR)/token_create.c $(TOKENS_DIR)/token_delete.c $(TOKENS_DIR)/token_utils.c $(TOKENS_DIR)/tokenise.c $(TOKENS_DIR)/tokenise_ext.c $(TOKENS_DIR)/token_create_handlers.c $(TOKENS_DIR)/token_create_arrow_handlers.c

# BASE
BASE_DIR = src/base
MINI_BASE_SRC = $(BASE_DIR)/mini_signals.c

# Environment
ENV_DIR = src/environment
MINI_ENV_SRC = $(ENV_DIR)/environment_create.c $(ENV_DIR)/environment_delete.c $(ENV_DIR)/environment_read.c $(ENV_DIR)/environment_expand.c $(ENV_DIR)/environment_serialize.c $(ENV_DIR)/environment_create_ext.c $(ENV_DIR)/environment_sorted.c

# Utils
UTILS_DIR = src/utils
MINI_UTILS_SRC = $(UTILS_DIR)/utils.c $(UTILS_DIR)/aesthetics.c

# Execution
EXEC_DIR = src/execution
MINI_EXEC_SRC = $(EXEC_DIR)/execute_utils.c $(EXEC_DIR)/execute_command.c $(EXEC_DIR)/execute.c $(EXEC_DIR)/execute_heredoc.c $(EXEC_DIR)/execute_pipe.c $(EXEC_DIR)/execute_redirect_in.c $(EXEC_DIR)/execute_append.c $(EXEC_DIR)/execute_redirect_out.c

MINI_SRC = $(MINI_ENV_SRC) $(MINI_UTILS_SRC) $(MINI_BASE_SRC) $(MINI_TOKENS_SRC) $(MINI_AST_SRC) $(MINI_EXEC_SRC) $(MINI_BUILTINS_SRC)
MAIN_SRC = src/main.c $(MINI_SRC)
MAIN_OBJ = $(MAIN_SRC:.c=.o)

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
TESTFLAGS = -fprofile-arcs -ftest-coverage
TEST_LIBS = -lcunit
RM = rm -rf

# Include Paths and Libraries
INC_LIBFT_GNL = -Ilibft/inc_libft/ -Ilibft/inc_gnl/ -Ilibft/inc_ft_printf/
INC = -Iinc/ $(INC_LIBFT_GNL)
LIBFT_INCLUDE = -L./libft -lft
LIBS = $(LIBFT_INCLUDE) -lreadline -lncurses

# Compilation rule for object files
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Main Application
$(NAME): $(MAIN_OBJ)
	@cd libft && make bonus
	mkdir -p $(OUT_DIR)
	$(CC) $(MAIN_OBJ) $(LIBS) -o $(OUT_DIR)/$(NAME)

# Testing Application
test: $(TEST_OBJ)
	@cd libft && make
	$(CC) $(TESTFLAGS) $(TEST_OBJ) $(LIBS) $(TEST_LIBS) -o test/test_minishell
	@echo "Running tests..."
	@cd test && ./test_minishell


# Standard Targets
all: $(NAME)

# Direct run
run: $(NAME)
	@./$(OUT_DIR)/$(NAME)

full: $(NAME)
	@./$(OUT_DIR)/$(NAME) --full

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(OUT_DIR)/$(NAME) --full

clean:
	$(RM) $(MAIN_OBJ) $(TEST_OBJ)
	@cd libft && make clean
	rm -rf $(OUT_DIR)

fclean: clean
	$(RM) $(NAME) test/test_minishell
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re test/test_minishell
