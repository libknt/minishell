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
#include <err.h>
#include <errno.h>

int		exit_status;

/*lexer */
t_token	*lexer(char **line, t_env *env);
/*lexer utils auote*/
bool	quate_flag(char *prompt, size_t *len, bool *dq, bool *sq);
/*lexer utils is*/
bool	is_ok(char *prompt, size_t len);
bool	is_blank(char c);
size_t	is_ope(char *line);
size_t	is_redirect(char *line);

/*token*/
void	token_addback(t_token **head, t_token *new);
t_token	*new_token(char *str, t_token_type type);

/*parser*/
t_node	*parser(t_token *token,char *line);
t_line	*make_line(t_token *token);
bool	find_redirect(t_token *token);
t_node	**add_node(t_node *node);
void	_err_parse_p(char *mes, bool *r);
void	_err_syntax_p(char *mes, bool *r);
void	addline_utils(t_line **line, t_token *token, t_redirect type);
void	line_addback(t_line **head, t_line *new);
t_line	*newline(t_token *token, t_redirect type);


/*execve*/
int	execve_simple_cmd(t_node *node);


char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*exec_filename(char *prompt);
void	_err(const char *e);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_split_free(char **dst);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	token_free(t_token **token);
void	expand(t_token *token);
bool	token_error(t_token *token);
void	tree_free(t_node *tree);
bool	parse_err(t_node *node);
bool	_err_syntax(char *mes);
void	print_t(t_token *token);
void	print_tree(t_node *node);
void	print_n(t_node *node);

char	**make_arr(t_node *node, int here);
void	_redirect_si(t_node *node);
int		_redirect(t_node *node);
void	restore_fd(t_node *node);
int		here_documents(t_node *node);
void	ex_toke(t_token **token, t_env *env);
// char	*get_next_line(int fd);
int		exec_tree(t_node *node);
int		exe_(t_node *node);
void	set_signal(void);
void	make_lstenv(t_env **s_env, char **envp);

void	print_line(t_line *line);
void	print_split(char **t);
void	print_t(t_token *token);

void	test(t_node *node);
#endif
