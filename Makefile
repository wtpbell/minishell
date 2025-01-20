NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRCDIR		= src
INCDIR		= include
OBJDIR		= objs
LIBFTDIR	= lib

SRCS		= $(SRCDIR)/main.c \
			  $(SRCDIR)/lexer/lexer.c \
			  $(SRCDIR)/lexer/token_utils.c \
			  $(SRCDIR)/lexer/quote_utils.c \
			  $(SRCDIR)/parser/parser.c \
			  $(SRCDIR)/parser/ast_utils.c \
			  $(SRCDIR)/parser/syntax.c \
			  $(SRCDIR)/expander/expander.c \
			  $(SRCDIR)/expander/env_utils.c



LIBFT		= $(LIBFTDIR)/libft.a
LIBS		= -L$(LIBFTDIR) -lft -lreadline

INCLUDES	= -I$(INCDIR) -I$(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFTDIR)

all: $(NAME)

clean:
	@make -C $(LIBFTDIR) clean
	$(RM) -r $(OBJDIR)

fclean: clean
	@make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
