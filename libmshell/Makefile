NAME		= libmshell.a
SRC			= calloc.c  \
			  memmove.c \
			  putchar.c \
			  putstr.c  \
			  strchr.c  \
			  strjoin.c \
			  strlcpy.c \
			  strncat.c \
			  strndup.c \
			  bzero.c   \
			  itoa.c    \
			  memcpy.c  \
			  memset.c  \
			  putendl.c \
			  split.c   \
			  strdup.c  \
			  strlcat.c \
			  strlen.c  \
			  strncmp.c \
			  substr.c
OBJS		= $(SRC:.c=.o)
CC 			= gcc
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
