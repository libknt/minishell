NAME 				=	minishell
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror
INCLUDE				=	-I ./include/ 

INCLUDE_READLINE	=	-I ~/.brew/opt/readline/include
LIB					=	$(LIBMSHELL) -L ~/.brew/opt/readline/lib

LIBMSHELLDIR		=	libmshell
LIBMSHELL			=	$(LIBMSHELLDIR)/libmshell.a

CFLAGS_DEBUG		=	-g -fsanitize=address

SRCS				=	srcs/buildin/buildin.c \
						srcs/buildin/buildin_simple.c \
						srcs/buildin/cd.c \
						srcs/buildin/cd2.c \
						srcs/buildin/echo.c \
						srcs/buildin/env.c \
						srcs/buildin/env2.c \
						srcs/buildin/exit.c \
						srcs/buildin/exit2.c \
						srcs/buildin/export.c \
						srcs/buildin/export2.c \
						srcs/buildin/pwd.c \
						srcs/buildin/unset.c \
						srcs/environ/expand.c \
						srcs/environ/expand_utils.c \
						srcs/environ/expand3.c \
						srcs/environ/make_lstenvp.c \
						srcs/environ/make_lstenvp_utils.c \
						srcs/environ/make_lstenvp_utils2.c \
						srcs/err/_err1.c \
						srcs/err/_err2.c \
						srcs/err/_err3.c \
						srcs/err/_err_utils.c \
						srcs/exe/exe.c \
						srcs/exe/exec_filename.c \
						srcs/exe/execve.c \
						srcs/exe/execve2.c \
						srcs/exe/execve_simple_cmd.c \
						srcs/exe/is_access.c \
						srcs/exe/make_arr.c \
						srcs/free/free.c \
						srcs/heredoc/heredoc.c \
						srcs/heredoc/heredoc_utils.c \
						srcs/lexer/lexer.c \
						srcs/lexer/lexer2.c \
						srcs/lexer/lexer_utils_is.c \
						srcs/lexer/lexer_utils_quote.c \
						srcs/lexer/t_free.c \
						srcs/lexer/token.c \
						srcs/lexer/token_error.c \
						srcs/main.c \
						srcs/parser/parse_err.c \
						srcs/parser/parser.c \
						srcs/parser/parser_line.c \
						srcs/parser/parser_line_utils.c \
						srcs/parser/parser_utils.c \
						srcs/redirect/redirect.c \
						srcs/redirect/redirect_adoption.c \
						srcs/redirect/redirect_left.c \
						srcs/redirect/redirect_right.c \
						srcs/redirect/redirect_utils.c \
						srcs/signal/signal.c \
						srcs/signal/signal2.c

OBJDIR   			= 	obj
OBJS  				= 	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

$(OBJDIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDE) $(INCLUDE_READLINE) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME):$(OBJS)
	make -C libmshell
	@mkdir -p .heredoc
	$(CC) $^ $(CFLAGS) $(LIB) -o $@ -lreadline

lib:
	make  -C libmshell

clean:
	$(RM) -r $(OBJDIR)
	make clean -C libmshell

fclean: clean
	$(RM) $(NAME)
	make fclean -C libmshell
	rm -f result

re : fclean all

debug:	CFLAGS += $(CFLAGS_DEBUG)
debug:	re

# readline:
# 	brew install readline
# #goinfre 
# brew:
# 	curl -fsSL https://raw.githubusercontent.com/mfunyu/config/main/42homebrew_install.sh | zsh
# #under HOME
# brew:
# 	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

.PHONY:
	all lib clean fclean re debug

