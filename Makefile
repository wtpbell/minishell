NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
OBJ_DIR = obj
INCLUDE_DIR = include
LIBFT_DIR = lib

SRC_FILES = $(SRC_DIR)/main.c

LEXER_FILES = $(LEXER_DIR)/tokenizer.c \
			  $(LEXER_DIR)/init/tokenizer_init.c \
			  $(LEXER_DIR)/token/token_create.c \
			  $(LEXER_DIR)/token/token_type.c \
			  $(LEXER_DIR)/processor/operator_handler.c \
			  $(LEXER_DIR)/processor/quote_handler.c \
			  $(LEXER_DIR)/processor/word_handler.c \
			  $(LEXER_DIR)/utils/whitespace.c \
			  $(LEXER_DIR)/utils/char_checks.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ = $(LEXER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

ALL_OBJ = $(OBJ_FILES) $(LEXER_OBJ)
ALL_SRC = $(SRC_FILES) $(LEXER_FILES)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/lexer/init
	@mkdir -p $(OBJ_DIR)/lexer/token
	@mkdir -p $(OBJ_DIR)/lexer/processor
	@mkdir -p $(OBJ_DIR)/lexer/utils

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(ALL_OBJ)
	$(CC) $(ALL_OBJ) $(LIBS) -o $(NAME)
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
