/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:49:59 by marai             #+#    #+#             */
/*   Updated: 2023/06/27 13:14:04 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libmshell/libmshell.h"
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
# define PATH_MAXLEN 4096
# define NO_QUOTE 0
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
/*buildin*/
// buildin_simple
int				buildin_simple(char *argv[], t_env **env);
//buildin
bool			is_buildin(char *str);
int				buildin(char *argv[], t_env **env);
t_status		*new_status(void);
//cd.c
int				cd(char *argv[], t_env **env, t_status *s);
int				move_to_home_or_rel_path(char *path[], t_env *env);
//cd2.c
char			*get_home_dir(t_env *env);
bool			is_home_set(char *home);
char			*make_home_path(char *path, char *home);
void			imple_pwd(t_env **head, t_status *s);
//echo.c
void			ft_echo(char **argv, t_status *s);
//env.c
void			env_buildin(char *argv[], t_env *env, t_status *s);
//env2.c
char			**make_env_args(t_env *env);
//exit.c
void			ft_exit(char **argv, t_status *s);
//exit2.c
void			check_sign(char *str);
//export.c
int				check_env_vari(char *argv);
void			ft_export(char *argv[], t_env **env, t_status *s);
//export2.c
char			**env_sort(char **envp);
char			**free_envp(char **envp, ssize_t len);
ssize_t			env_num(t_env *env);
//pwd.c
char			*get_pwd(t_status *s);
void			ft_pwd(t_status *s);
//unset.c
void			unset(char *argv[], t_env **env, t_status *s);

/*environ*/
//expand.c
char			*ft_strjoin_free(char *str1, char *str2);
char			*expand(char *line, t_env *env);
char			*expand_all_env(char *line, t_env *env);
void			expand_token(t_token **token, t_env *env, bool f);
//expand2.c
bool			is_skip(char c, int *status);
size_t			env_len(char *line);
size_t			add_char(char **str, char *line);
size_t			expand_env(char **str, char *line, t_env *env);
//expand3.c
bool			is_alpha_under(char c);
bool			is_alpha_num_under(char c);
bool			is_identifier(const char *s);
int				is_quote(char c);
bool			is_heredoc_flag(char *word);
//make_lstenvp_utils.c
t_env			*new_lstenv(char *envp);
//make_lstenvp_utils2.c
void			ft_env_addback(t_env **env, t_env *new);
void			make_lstenv(t_env **s_env, char **envp);
//make_lstenvp.c
t_env			*search_key_in_list(t_env **env, t_env *new);
void			replace_node_in_list(t_env **head, t_env **env_node, \
			t_env *new);
t_env			*make_env(char *key, char *value);

/*err*/
//_err_utils.c
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
//_err1.c
void			_err(const char *e);
int				_err_malloc(void);
int				_err_fork(void);
int				_err_wait(int status);
//_err2.c
bool			_err_syntax(char *m);
void			_err_syntax_p(char *m, bool *r);
void			_err_parse_p(char *m, bool *r);
void			*_err_nofile(t_node *node, char *m);
void			_err_cmd_not_found(char *m);
//_err3.c
void			_err_minishell(char *m);
void			_err_is_directory(char *m);
void			_err_permission(char *m);
void			_err_heredoc(char *m);

/*exe*/
//exec.c
char			**access_cmd_path(t_node *node, char **envp);
int				exec_tree(t_node *node, t_env **env, int atty);
int				exe_(t_node *node, t_env **env);
//exec_filename.c
char			*exec_filename(char *prompt, char **envp);
//execve_simple_cmd.c
int				execve_simple_cmd(t_node *node, t_env **env);
//execve.c
int				exec(t_node *node, t_env **env, int fd1, int atty);
//execve2.c
int				command_found(char **argv, char **envp);
void			close_pipe(t_node *node, int rw[2], int fd1);
int				revert_free(t_node *node, char **argv, char **envp, int rw[2]);
bool			check_argv(char **argv, t_node *node);
//is_access.c
int				is_directory(const char *str);
int				is_file_accessible(char *str);
//make_arr.c
char			**make_arr(t_node *node);

/*free*/
//free.c
void			tree_free(t_node *tree);

/*heredoc*/
//heredoc_utils.c
void			set_status(int status, t_node *node);
bool			is_heredoc(t_line *line);
char			*ft_rename(char *x);
char			*ft_rename_dir(char *x);
bool			is_heredocfile(void);
//heredoc.c
t_fd			*new_fd(void);
t_fd			*heredoc(t_heredoc_var *v, t_env *env, t_node *node);

/*lexer*/
//lexer_utils_is.c
bool			is_blank(char c);
size_t			is_ope(char *line);
size_t			is_redirect(char *line);
bool			is_ok(char *prompt, size_t len);
//lexer_utils_quote.c
bool			quate_flag(char *prompt, size_t *len, bool *dq, bool *sq);
//lexer.c
t_token			*lexer(char **line, t_env *env);
//lexer2.c
ssize_t			wordlen(char *prompt, t_data_t *d);
t_token_type	find_type(char *tmp);
void			*lexer_err_free(char **line, t_token **token);
void			check_redirect(t_token *token);
//t_free.c
void			token_free(t_token **token);
//token_error.c
bool			token_error(t_token *token);
//token.c
void			token_addback(t_token **head, t_token *new);
t_token			*new_token(char *str, t_token_type type);

/*parser*/
//parse_err.c
bool			parse_err(t_node *node);
//parser_line_utils.c
t_line			*newline(t_token *token, t_redirect type);
void			line_addback(t_line **head, t_line *new);
//parser_line.c
t_line			*make_line(t_token *token);
//parser_utils.c
t_node			**add_node(t_node *node);
//parser.c
bool			find_redirect(t_token *token);
t_node			*parser(t_token *token, char *line);

/*redirect*/
//redirect_adoption.c
void			redirect_adoption(t_fds *fds);
//redirect_left.c
void			*close_file(t_fd *fd);
t_fd			*redirect_left(t_node *node, t_line *line, \
	t_env *env, t_fd *fd);
//redirect_right
t_fd			*redirect_right(t_node *node, t_line *line);
//redirect_utils.c
void			*revert_redirect(t_fds *fd);
void			revert_redirect_pipe(t_fds *fd, int rw[2]);
//redirect.c
void			add_redirect(t_node *node, t_env *env);
t_fds			*redirect_check(t_node *node, t_env *env);

/*signal*/
//signal.c
void			set_signal(void);
void			block_signal(void);
void			reset_signal(void);
//signal2.c
void			sig_handler(int sig);
int				exec_action(void);
int				check_state(void);

#endif
