NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
COMMON_DIR = $(SRC_DIR)/common
EXECUTOR_DIR = $(SRC_DIR)/executor
BUITLIN_DIR = $(SRC_DIR)/builtin
ENV_DIR = $(SRC_DIR)/env
EXPANDER_DIR = $(SRC_DIR)/expander
OBJ_DIR = obj
INCLUDE_DIR = include
LIBFT_DIR = lib

SRC_FILES = $(SRC_DIR)/main.c

LEXER_FILES = $(LEXER_DIR)/tokenizer.c \
			  $(LEXER_DIR)/init/tokenizer_init.c \
			  $(LEXER_DIR)/token/token_create.c \
			  $(LEXER_DIR)/token/token_type.c \
			  $(LEXER_DIR)/token/token_utils.c \
			  $(LEXER_DIR)/handler/operator_handler.c \
			  $(LEXER_DIR)/handler/quote_handler.c \
			  $(LEXER_DIR)/handler/quote_validate_handler.c \
			  $(LEXER_DIR)/handler/quote_extract_handler.c \
			  $(LEXER_DIR)/handler/quote_create_handler.c \
			  $(LEXER_DIR)/handler/wildcard_handler.c \
			  $(LEXER_DIR)/handler/word_handler.c \
			  $(LEXER_DIR)/utils/char_check.c \
			  $(LEXER_DIR)/utils/word_utils.c \

PARSER_FILES = $(PARSER_DIR)/parser.c \
			   $(PARSER_DIR)/core/ast.c \
			   $(PARSER_DIR)/core/parser_ast.c \
			   $(PARSER_DIR)/handler/command_handler.c \
			   $(PARSER_DIR)/handler/redirection_handler.c \
			   $(PARSER_DIR)/handler/pipeline_handler.c \
			   $(PARSER_DIR)/handler/pipeline_sequence_handler.c \
			   $(PARSER_DIR)/handler/pipe_redirection_handler.c \
			   $(PARSER_DIR)/handler/logic_handler.c \
			   $(PARSER_DIR)/handler/group_handler.c \
			   $(PARSER_DIR)/handler/sequence_handler.c \
			   $(PARSER_DIR)/validator/command_validator.c \
			   $(PARSER_DIR)/validator/parser_validator.c \
			   $(PARSER_DIR)/validator/redirection_validator.c \
			   $(PARSER_DIR)/validator/syntax_validator.c \
			   $(PARSER_DIR)/validator/subshell_validator.c \
			   $(PARSER_DIR)/validator/token_validator.c \
			   $(PARSER_DIR)/utils/command_utils.c \
			   $(PARSER_DIR)/utils/free_utils.c \
			   $(PARSER_DIR)/utils/error_messages.c \
			   $(PARSER_DIR)/utils/error_utils.c \
			   $(PARSER_DIR)/utils/group_utils.c \
			   $(PARSER_DIR)/utils/logic_utils.c \
			   $(PARSER_DIR)/utils/redirection_utils.c \

ENV_FILES 	 = $(ENV_DIR)/env_init.c \
			   $(ENV_DIR)/env_utils2.c \
			   $(ENV_DIR)/env_utils1.c \
			   $(ENV_DIR)/env_set.c \

BUILTIN_FILES =  $(BUITLIN_DIR)/builtin_exit.c \
				 $(BUITLIN_DIR)/builtin_echo.c \
				 $(BUITLIN_DIR)/builtin_export.c \
				 $(BUITLIN_DIR)/builtin_cd.c \
				 $(BUITLIN_DIR)/builtin.c \
				 $(BUITLIN_DIR)/builtin_utils1.c \
				 $(BUITLIN_DIR)/builtin_utils2.c \

EXECUTOR_FILES = $(EXECUTOR_DIR)/executor.c \
				 $(EXECUTOR_DIR)/execute_tree.c \
				 $(EXECUTOR_DIR)/exit_update.c \
				 $(EXECUTOR_DIR)/cmd_utils.c \
				 $(EXECUTOR_DIR)/path_utils.c \
				 $(EXECUTOR_DIR)/heredoc_utils.c \
				 $(EXECUTOR_DIR)/pipe_utils.c \
				 $(EXECUTOR_DIR)/wait_utils.c \
				 $(EXECUTOR_DIR)/execute_process.c \
				 $(EXECUTOR_DIR)/execute_pipe.c \
				 $(EXECUTOR_DIR)/execute_heredoc.c \
				 $(EXECUTOR_DIR)/execute_redir.c \
				 $(EXECUTOR_DIR)/execute_cmd.c \

COMMON_FILES = $(COMMON_DIR)/signal.c \
				$(COMMON_DIR)/signal_handler.c \
				$(COMMON_DIR)/signal_utils1.c \
				$(COMMON_DIR)/prompt.c \
				$(COMMON_DIR)/mem_split.c \
				$(COMMON_DIR)/mem_realloc.c \
				$(COMMON_DIR)/mem_free.c \
				$(COMMON_DIR)/error.c \
				$(COMMON_DIR)/root_node.c \

EXPANDER_FILES = $(EXPANDER_DIR)/expander.c \
				$(EXPANDER_DIR)/expander_args_processor.c \
				$(EXPANDER_DIR)/expander_args_expansion.c \
				$(EXPANDER_DIR)/expander_dollar.c \
				$(EXPANDER_DIR)/expander_exit_status.c \
				$(EXPANDER_DIR)/expander_expansion_handler.c \
				$(EXPANDER_DIR)/expander_quotes_utils.c \
				$(EXPANDER_DIR)/expander_quotes.c \
				$(EXPANDER_DIR)/expander_utils.c \
				$(EXPANDER_DIR)/expander_variables.c \
				$(EXPANDER_DIR)/heredoc_expander.c \
				$(EXPANDER_DIR)/mixed_wildcard_handler.c \
				$(EXPANDER_DIR)/wildcard_array_utils.c \
				$(EXPANDER_DIR)/wildcard_expander_utils.c\
				$(EXPANDER_DIR)/wildcard_expander.c \
				$(EXPANDER_DIR)/wildcard_replacement.c \
				$(EXPANDER_DIR)/wildcard_filesystem.c \

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ = $(LEXER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
PARSER_OBJ = $(PARSER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
ENV_OBJ = $(ENV_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXECUTOR_OBJ = $(EXECUTOR_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BUILTIN_OBJ = $(BUILTIN_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
COMMON_OBJ = $(COMMON_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXPANDER_OBJ = $(EXPANDER_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

ALL_OBJ = $(OBJ_FILES) $(LEXER_OBJ) $(PARSER_OBJ) $(ENV_OBJ) $(BUILTIN_OBJ) $(EXECUTOR_OBJ) $(COMMON_OBJ) $(EXPANDER_OBJ)
ALL_SRC = $(SRC_FILES) $(LEXER_FILES) $(PARSER_FILES) $(ENV_FILES) $(BUILTIN_FILES) $(EXECUTOR_FILES) $(COMMON_FILES) $(EXPANDER_FILES)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/lexer/handler
	@mkdir -p $(OBJ_DIR)/lexer/heredoc
	@mkdir -p $(OBJ_DIR)/lexer/init
	@mkdir -p $(OBJ_DIR)/lexer/token
	@mkdir -p $(OBJ_DIR)/lexer/utils
	@mkdir -p $(OBJ_DIR)/parser/core
	@mkdir -p $(OBJ_DIR)/parser/handler
	@mkdir -p $(OBJ_DIR)/parser/utils
	@mkdir -p $(OBJ_DIR)/parser/validator
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/executor
	@mkdir -p $(OBJ_DIR)/executor/error
	@mkdir -p $(OBJ_DIR)/builtin
	@mkdir -p $(OBJ_DIR)/common
	@mkdir -p $(OBJ_DIR)/common/utils/memory
	@mkdir -p $(OBJ_DIR)/expander

$(LIBFT):
	@echo "\033[1;32mCompiling...\033[0m"
	@make -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(ALL_OBJ)
	@$(CC) $(ALL_OBJ) $(LIBS) -o $(NAME)
	@echo "\033[1;36m"
	@echo "                                                                         "
	@echo "   ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗        "
	@echo "   ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║        "
	@echo "   ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║        "
	@echo "   ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║        "
	@echo "   ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗   "
	@echo "   ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝   "
	@echo "                                                made by spyun & bewong   "
	@echo "\033[0m"
	@echo "\033[1;32mMinishell compiled successfully!\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "\033[1;33mObject files cleaned!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "\033[1;34mEverything cleaned!\033[0m"

re: fclean all

.PHONY: all clean fclean re
