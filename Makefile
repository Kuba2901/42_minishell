# Project name
NAME = minishell
OUT_DIR = output

# Source and Object files
TOK_DIR = src/parsing/tokenisation
AST_DIR = src/parsing/ast
ENV_DIR = src/parsing/environment
MINI_ENV_SRC = $(ENV_DIR)/environment.c
MINI_AST_SRC = $(AST_DIR)/parse.c
MINI_TOKENISATION_SRC = $(TOK_DIR)/tokens.c $(TOK_DIR)/single_token_utils.c $(TOK_DIR)/token_list_utils.c $(TOK_DIR)/tokens_handlers.c $(TOK_DIR)/tokens_handler_01.c 
MINI_SRC = $(MINI_TOKENISATION_SRC) $(MINI_AST_SRC) $(MINI_ENV_SRC)
MAIN_SRC = src/main.c $(MINI_SRC)
MAIN_OBJ = $(MAIN_SRC:.c=.o)

# Testing files
TEST_SRC = test/test_minishell.c $(MINI_SRC)
TEST_OBJ = $(TEST_SRC:.c=.o)

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
LIBS = $(LIBFT_INCLUDE) -lreadline

# Compilation rule for object files
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Main Application
$(NAME): $(MAIN_OBJ)
	@cd libft && make
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

clean:
	$(RM) $(MAIN_OBJ) $(TEST_OBJ)
	@cd libft && make clean

fclean: clean
	$(RM) $(NAME) test/test_minishell
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re test/test_minishell
