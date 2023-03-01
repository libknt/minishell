#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "struct.h"
# include <ctype.h>
# include <fcntl.h>
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		exe(t_node *node);
char	**ft_split(char const *s, char c);
char	*exec_filename(char *prompt);
t_token	*lexer(char **line);
void	_err(const char *e);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_split_free(char **dst);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	token_free(t_token **token);
void	expand(t_token *token);
bool	token_error(t_token *token);
t_node	*parser(t_token *token);
void	tree_free(t_node *tree);
bool	parse_err(t_node *node);

void	print_t(t_token *token);
void	print_tree(t_node *node);
void	print_n(t_node *node);

char	**make_arr(t_node *node);
void	_redirect(t_node *node);
void	restore_fd(t_node *node);
void	here_documents(t_node *node);
char	*get_next_line(int fd);
int		exec_tree(t_node *node);
int		exe_(t_node *node);
void	set_signal(void);
void	make_lstenv(t_env **s_env, char **envp);

void	print_line(t_line *line);
void	print_split(char **t);
t_node	**add_node(t_node *node);

void test(t_node *node);
#endif
