#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <limits.h>
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "struct.h"

int	exe(char *prompt);
char	**ft_split(char const *s, char c);
char	*exec_filename( char *prompt);
t_token	*lexer(char **line);
void	_err(const char *e);
char	*ft_strjoin(char const *s1, char const *s2);
#endif
