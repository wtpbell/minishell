NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDFLAGS = -fsanitize=address

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
COMMON_DIR = $(SRC_DIR)/common
OBJ_DIR = obj
INCLUDE_DIR = -I./include
LIBFT_DIR = lib

SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/banner.c

LEXER_FILES = $(LEXER_DIR)/tokenizer.c \
			  $(LEXER_DIR)/init/tokenizer_init.c \
			  $(LEXER_DIR)/token/token_create.c \
			  $(LEXER_DIR)/token/token_type.c \
			  $(LEXER_DIR)/handler/expansion_braced_handler.c \
			  $(LEXER_DIR)/handler/expansion_handler.c \
			  $(LEXER_DIR)/handler/operator_handler.c \
			  $(LEXER_DIR)/handler/quote_handler.c \
			  $(LEXER_DIR)/handler/quote_validator.c \
			  $(LEXER_DIR)/handler/tilde_handler.c \
			  $(LEXER_DIR)/handler/word_handler.c \
			  $(LEXER_DIR)/heredoc/heredoc_handler.c \
			  $(LEXER_DIR)/heredoc/heredoc_expansion.c \
			  $(LEXER_DIR)/utils/char_check.c \
			  $(LEXER_DIR)/utils/expansion_utils.c \

PARSER_FILES = $(PARSER_DIR)/parser.c \
			   $(PARSER_DIR)/core/ast.c \
			   $(PARSER_DIR)/handler/command_handler.c \
			   $(PARSER_DIR)/handler/redirection_handler.c \
			   $(PARSER_DIR)/handler/pipeline_handler.c \
			   $(PARSER_DIR)/handler/logic_handler.c \
			   $(PARSER_DIR)/handler/logic_parser.c \
			   $(PARSER_DIR)/handler/group_handler.c \
			   $(PARSER_DIR)/validator/command_validator.c \
			   $(PARSER_DIR)/validator/syntax_validator.c \
			   $(PARSER_DIR)/utils/free_utils.c

COMMON_FILES = $(COMMON_DIR)/utils.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ = $(LEXER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
PARSER_OBJ = $(PARSER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

ALL_OBJ = $(OBJ_FILES) $(LEXER_OBJ) $(PARSER_OBJ)
ALL_SRC = $(SRC_FILES) $(LEXER_FILES) $(PARSER_FILES)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/lexer/init
	@mkdir -p $(OBJ_DIR)/lexer/token
	@mkdir -p $(OBJ_DIR)/lexer/handler
	@mkdir -p $(OBJ_DIR)/lexer/utils
	@mkdir -p $(OBJ_DIR)/parser/core
	@mkdir -p $(OBJ_DIR)/parser/handlers

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
