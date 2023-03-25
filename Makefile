NAME 		=	minishell
CC			=	cc

# CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
# CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=leak
CFLAGS		=	-Wall -Wextra -Werror
INCLUDE		=	-I ./include/
# SRCS		= srcs/main.c\
# 			  srcs/exe/exe.c
SRCS		= $(shell find srcs/ -name "*.c" )


OBJDIR   = obj
OBJS  = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))



$(OBJDIR)/%.o: %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all: $(NAME)

$(NAME):$(OBJS)
	@mkdir -p .heredoc
	$(CC) $^ $(CFLAGS) -o $@ -lreadline

#$(NAME):$(OBJS)
#	@mkdir -p .heredoc
#	make -C libmshell
#	$(CC) $^ $(CFLAGS) libmshell/libmshell.a -o $@ -lreadline
leak :
	sh leak.sh

clean:
	$(RM) -r $(OBJDIR)
	$(RM) .*.heredoc

fclean: clean
	$(RM) $(NAME)

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
