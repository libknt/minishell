#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "struct.h"
# include <ctype.h>
# include <dirent.h>
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

# define WRITE 1
# define READ 0
size_t		env_len(char *envp);
void		add_env(t_env **env, char *envp, size_t len);
void		add_value(t_env **env, char *envp, size_t len);
t_env		*new_lstenv(char *envp);
t_env		*env_last(t_env *env);
void		*_err_nofile(t_node *node, char *m);
int			_err_fork(void);
void		_err_cmd_not_found(char *m);
int			is_quote(char c);
bool		is_alpha_under(char c);
bool		is_alpha_num_under(char c);
bool		is_identifier(const char *s);
ssize_t		vari_end(char *line);
char		*find_env(char *str, t_env *env);
ssize_t		find_env_len(char *str, t_env *env);
ssize_t		calc_expand_len(char *line, t_env *env, ssize_t len);
ssize_t		vari_expand_len(char *line, t_env *env);
bool		is_heredocfile(void);
void		_err_heredoc(char *m);
int			exec(t_node *node, t_env *env, int fd1, int atty);
char		**access_cmd_path(t_node *node, char **envp);
char		*ft_rename(char *x);
char		*ft_rename_dir(char *x);
char		*ft_strdup(const char *s1);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char const *s1, char const *s2);
void		add_redirect(t_node *node, t_env *env);
int			_err_wait(int status);

/*redirect*/
char		*expand_quote(char *line);
char		*vari_expand(char *line, t_env *env);
t_fds		*redirect_check(t_node *node, t_env *env);
void		*revert_redirect(t_fds *fd);
t_fd		*redirect_right(t_node *node, t_line *line);
t_fd		*redirect_left(t_node *node, t_line *line, t_env *env, t_fd *fd);
t_fd		*heredoc(t_heredoc_var *v, t_env *env, t_node *node);
void		redirect_adoption(t_fds *fds);
void		revert_redirect_pipe(t_fds *fd, int rw[2]);

void		ft_pwd(t_status *s);
void		ft_echo(char **argv, t_status *s);
void		ft_exit(char **argv, t_status *s);
/*lexer */
t_token		*lexer(char **line, t_env *env);
/*lexer utils auote*/
bool		quate_flag(char *prompt, size_t *len, bool *dq, bool *sq);
/*lexer utils is*/
bool		is_ok(char *prompt, size_t len);
bool		is_blank(char c);
size_t		is_ope(char *line);
size_t		is_redirect(char *line);

/*token*/
void		token_addback(t_token **head, t_token *new);
t_token		*new_token(char *str, t_token_type type);

/*parser*/
t_node		*parser(t_token *token, char *line);
t_line		*make_line(t_token *token);
bool		find_redirect(t_token *token);
t_node		**add_node(t_node *node);
void		_err_parse_p(char *m, bool *r);
void		_err_syntax_p(char *m, bool *r);
void		addline_utils(t_line **line, t_token *token, t_redirect type);
void		line_addback(t_line **head, t_line *new);
t_line		*newline(t_token *token, t_redirect type);

/*execve*/
int			execve_simple_cmd(t_node *node, t_env *env);

char		**ft_split(char const *s, char c);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*exec_filename(char *prompt, char **envp);
void		_err(const char *e);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_split_free(char **dst);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		token_free(t_token **token);
bool		token_error(t_token *token);
void		tree_free(t_node *tree);
bool		parse_err(t_node *node);
void		print_t(t_token *token);
void		print_tree(t_node *node);
void		print_n(t_node *node);

char		**make_arr(t_node *node);
void		expand_token(t_token **token, t_env *env);
// char	*get_next_line(int fd);

int			exec_tree(t_node *node, t_env *env,int atty);
int			exe_(t_node *node, t_env *env);
void		set_signal(void);
void		make_lstenv(t_env **s_env, char **envp);

void		print_line(t_line *line);
void		print_split(char **t);
void		print_t(t_token *token);

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		ft_env_addback(t_env **env, t_env *new);
void		ft_export(char *argv[], t_env **env, t_status *s);
char		**make_env_args(t_env *env);
ssize_t		env_num(t_env *env);
char		**free_envp(char **envp, ssize_t len);
/*expand*/
bool		is_identifier(const char *s);
/*buildin*/
bool		is_buildin(char *str);
void		env_buildin(char *argv[], t_env *env, t_node *node, t_status *s);
int			execve_cmd(char **argv, char **envp, t_node *node);
int			buildin(char *argv[], t_env **env, t_node *node);
int			buildin_simple(char *argv[], t_env **env, t_node *node);
void		unset(char *argv[], t_env **env, t_status *s);
int			cd(char *argv[], t_env *env, t_status *s);
char		*ft_itoa(int n);
bool		_err_syntax(char *m);
int			_err_malloc(void);
t_status	*new_status(void);
void		reset_signal(void);
void		wait_process(void);
int			check_state(void);
int			exec_action(void);
void		_err_minishell(char *m);

void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);

char		**env_sort(char **envp);
char		**free_envp(char **envp, ssize_t len);
ssize_t		env_num(t_env *env);

char		**make_env_args(t_env *env);

int			command_found(char **argv, char **envp);
void		close_pipe(t_node *node, int rw[2], int fd1);
int			revert_free(t_node *node, char **argv, char **envp, int rw[2]);
bool		check_argv(char **argv, t_node *node);
int			is_quote(char c);

ssize_t		vari_end(char *line);
ssize_t		find_env_len(char *str, t_env *env);
ssize_t		calc_expand_len(char *line, t_env *env, ssize_t len);
ssize_t		vari_expand_len(char *line, t_env *env);
char		*find_env(char *str, t_env *env);

t_token	*token_last(t_token *token);
bool is_file_access(char *str);
#endif
