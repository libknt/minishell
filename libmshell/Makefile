NAME		= 	libmshell.a
SRC			=	calloc.c\
				isspace.c\
				memcpy.c\
				putchar.c\
				split.c\
				strdup.c\
				strlcpy.c\
				strncmp.c\
				atol.c\
				isalpha.c\
				itoa.c\
				memmove.c\
				putendl.c\
				strchr.c\
				strjoin.c\
				strlen.c\
				strndup.c\
				bzero.c\
				isdigit.c\
				memset.c\
				putstr.c\
				strcmp.c\
				strlcat.c\
				strncat.c\
				substr.c \

OBJS		= $(SRC:.c=.o)
CC 			= cc
INCLUDE		= -I ./
CFLAGS		= -Wall -Wextra -Werror $(INCLUDE)

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $^

clean :
	$(RM) $(OBJS_BONUS) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re