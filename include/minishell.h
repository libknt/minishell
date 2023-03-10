#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "struct.h"
# include <ctype.h>
# include <err.h>
# include <errno.h>
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

int		exit_status;

/*redirect*/
char	*expand_quote(char *line);
char	*vari_expand(char *line, t_env *env);
t_fds	*redirect_check(t_node *node, t_env *env);
void	revert_redirect(t_fds *fd);
t_fd	*redirect_right(t_line *line);
t_fd	*redirect_left(t_line *line, t_env *env);
t_fd	*heredoc(char *eof, t_env *env);

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
t_node	*parser(t_token *token, char *line);
t_line	*make_line(t_token *token);
bool	find_redirect(t_token *token);
t_node	**add_node(t_node *node);
void	_err_parse_p(char *mes, bool *r);
void	_err_syntax_p(char *mes, bool *r);
void	addline_utils(t_line **line, t_token *token, t_redirect type);
void	line_addback(t_line **head, t_line *new);
t_line	*newline(t_token *token, t_redirect type);

/*execve*/
int		execve_simple_cmd(t_node *node, t_env *env);

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

char	**make_arr(t_node *node);
void	expand_token(t_token **token, t_env *env);
// char	*get_next_line(int fd);

int		exec_tree(t_node *node, t_env *env);
int		exe_(t_node *node, t_env *env);
void	set_signal(void);
void	make_lstenv(t_env **s_env, char **envp);

void	print_line(t_line *line);
void	print_split(char **t);
void	print_t(t_token *token);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		cd(char *argv[], t_env *env);
void	ft_env_addback(t_env **env, t_env *new);
t_env	*new_lstenv(char *envp);
void	ft_export(char *argv[], t_env **env);
void	test(t_node *node);
char	**make_env_args(t_env *env);
ssize_t	env_num(t_env *env);
char	**free_envp(char **envp, ssize_t len);
/*buildin*/
bool	is_buildin(char *str);
void	env_buildin(char *argv[], t_env *env);
int		buildin(char *argv[], t_env **env);
int		cd(char *argv[], t_env *env);
#endif
