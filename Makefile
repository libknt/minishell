NAME 		=	minishell
CC			=	cc

# CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
# CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=leak
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=leak -fsanitize=address
INCLUDE		=	-I ./include/ -I ~/.brew/opt/readline/include
# INCLUDE		=	-I ./include/ -I /goinfre/kyoda/.brew/opt/readline/include
# SRCS		= srcs/main.c\
# 			  srcs/exe/exe.c
SRCS		= $(shell find srcs/ -name "*.c" )

LIBMSHELLDIR	=	libmshell
LIBMSHELL		=	$(LIBMSHELLDIR)/libmshell.a
LIB			=	$(LIBMSHELL) -L ~/.brew/opt/readline/lib
# LIB			=	$(LIBMSHELL) -L /goinfre/kyoda/.brew/opt/readline/lib


OBJDIR   = obj
OBJS  = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))



$(OBJDIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME):$(OBJS)
	make -C libmshell
	@mkdir -p .heredoc
	$(CC) $^ $(CFLAGS) $(LIB) -o $@ -lreadline

#$(NAME):$(OBJS)
#	@mkdir -p .heredoc
#	make -C libmshell
#	$(CC) $^ $(CFLAGS) libmshell/libmshell.a -o $@ -lreadline
leak :
	sh leak.sh

clean:
	$(RM) -r $(OBJDIR)
	$(RM) .*.heredoc
	$(RM) ./.heredoc/.*.heredoc

fclean: clean
	$(RM) $(NAME)
	make fclean -C libmshell
	rm -f result

re : fclean all
	./minishell

t : all
	sh test.sh

var:
	rm -f log/log.txt
	valgrind --leak-check=full --show-leak-kinds=all -s -q ./minishell
varl:
	rm -f log/log.txt
	valgrind --log-file="log/log.txt" --leak-check=full --show-leak-kinds=all -s -q ./minishell



test:
	$(RM) -f a.out cpm exit42 infinite_loop out print_args result 
	@make --no-print-directory
	sleep 1;
	bash test.sh

# t:
# 	make all
# 	make -C minishell-tester
# 	./minishell
# 	make test -C minishell-tester

# tc:
# 	make fclean -C minishell-tester

# ret:tc t

# test :
# 	@mkdir -p log
# 	testcase

# echo:
# 	make echo -C minishell-tester

# exit:
# 	make exit -C minishell-tester
# path:
# 	make path -C minishell-tester
# redirect:
# 	make redirect -C minishell-tester

# syntax_error:
# 	make syntax_error -C minishell-tester

# env:
# 	make env -C minishell-tester

# exp:
# 	make exp -C minishell-tester

# pwd:
# 	make pwd -C minishell-tester

# simple:
# 	make simple -C minishell-tester

# unset:
# 	make unset -C minishell-tester

.PHONY:
		all clean fclean re libft t
