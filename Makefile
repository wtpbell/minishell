NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -fsanitize=address

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXECUTOR_DIR = $(SRC_DIR)/executor
BUITLIN_DIR = $(SRC_DIR)/builtin
ENV_DIR = $(SRC_DIR)/env
OBJ_DIR = obj
INCLUDE_DIR = include
LIBFT_DIR = lib

SRC_FILES = $(SRC_DIR)/main.c

LEXER_FILES = $(LEXER_DIR)/tokenizer.c \
			  $(LEXER_DIR)/init/tokenizer_init.c \
			  $(LEXER_DIR)/token/token_create.c \
			  $(LEXER_DIR)/token/token_type.c \
			  $(LEXER_DIR)/handler/operator_handler.c \
			  $(LEXER_DIR)/handler/quote_handler.c \
			  $(LEXER_DIR)/handler/word_handler.c \
			  $(LEXER_DIR)/utils/char_checks.c

PARSER_FILES = $(PARSER_DIR)/parser.c \
			   $(PARSER_DIR)/core/ast.c \
			   $(PARSER_DIR)/handler/command_handler.c \
			   $(PARSER_DIR)/handler/redirection_handler.c \
			   $(PARSER_DIR)/handler/pipeline_handler.c \
			   $(PARSER_DIR)/handler/logic_handler.c \
			   $(PARSER_DIR)/handler/logic_parser.c \
			   $(PARSER_DIR)/handler/group_handler.c \
			   $(PARSER_DIR)/utils/free_utils.c

ENV_FILES 	 = $(ENV_DIR)/env_init.c \
			   $(ENV_DIR)/env_utils.c

EXECUTOR_FILES = $(EXECUTOR_DIR)/executor.c \
				 $(EXECUTOR_DIR)/execute_tree.c \
				 $(EXECUTOR_DIR)/utils/exit_update.c \

BUILTIN_FILES =  $(BUILTIN_DIR)/builtin/builtin_exit.c \
				 $(BUILTIN_DIR)/builtin/builtin_export.c \
				 $(BUILTIN_DIR)/builtin/builtin_cd.c \
				 $(BUILTIN_DIR)/builtin/builtin.c \
				 $(BUILTIN_DIR)/error/error.c 

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ = $(LEXER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
PARSER_OBJ = $(PARSER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ENV_OBJ = $(ENV_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXECUTOR_OBJ = $(EXECUTOR_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BUILTIN_DIR = $(BUILTIN_DIR:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

ALL_OBJ = $(OBJ_FILES) $(LEXER_OBJ) $(PARSER_OBJ) $(ENV_OBJ) $(EXECUTOR_OBJ)
ALL_SRC = $(SRC_FILES) $(LEXER_FILES) $(PARSER_FILES) $(ENV_FILES) $(EXECUTOR_FILES)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/lexer/init
	@mkdir -p $(OBJ_DIR)/lexer/token
	@mkdir -p $(OBJ_DIR)/lexer/handler
	@mkdir -p $(OBJ_DIR)/lexer/utils
	@mkdir -p $(OBJ_DIR)/parser/core
	@mkdir -p $(OBJ_DIR)/parser/handlers
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/executor
	@mkdir -p $(OBJ_DIR)/executor/utils
	@mkdir -p $(OBJ_DIR)/builtin/builtin
	@mkdir -p $(OBJ_DIR)/builtin/error

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(ALL_OBJ)
	$(CC) $(ALL_OBJ) $(LIBS) $(LDFLAGS) -o $(NAME)
	@echo "Minishell compiled successfully!"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "Object files cleaned!"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "Everything cleaned!"

re: fclean all

.PHONY: all clean fclean re
