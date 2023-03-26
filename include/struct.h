/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:57:25 by keys              #+#    #+#             */
/*   Updated: 2023/03/26 16:49:22 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <stdio.h>

typedef struct s_heredoc_var	t_heredoc_var;
struct							s_heredoc_var
{
	int							fd;
	char						*eof;
	bool						flag;
};

typedef struct s_status			t_status;
struct							s_status
{
	bool						f;
	int							buildin_type;
	int							status;
	char						*err_ms;
};
typedef struct s_fd				t_fd;
struct							s_fd
{
	int							std_fd;
	int							file;
	int							file_new;
	int							std_fd_new;
};
typedef struct s_fds			t_fds;
struct							s_fds
{
	t_fd						*fd_r;
	t_fd						*fd_l;
};

typedef enum e_token_type		t_token_type;
enum							e_token_type
{
	WORD,
	RESERVED,
	OP,
	T_EOF,
	EX_WORD,
};

typedef struct s_token			t_token;
struct							s_token
{
	t_token						*next;
	t_token_type				type;
	char						*word;
	bool						*ex_heredoc_flag;
};

typedef struct s_data_t			t_data_t;
struct							s_data_t
{
	ssize_t						len;
	size_t						i;
	bool						sq;
	bool						dq;
	t_token						*head;
	t_token						*token;
	char						*word;
	char						*prompt;
};

typedef struct s_env			t_env;
struct							s_env
{
	char						*key;
	char						*value;
	t_env						*prev;
	t_env						*next;
};

typedef enum e_redirect			t_redirect;
enum							e_redirect
{
	PIPE,
	CMDLINE,
	REDIRECT,
	FILENAME,
	T_EOF_R,
};

typedef struct s_line			t_line;
struct							s_line
{
	t_redirect					type;
	t_token						*token;
	t_line						*next;
};

typedef struct s_node			t_node;
struct							s_node
{
	int							status;
	t_line						*line;
	t_fds						*fds;
	t_node						*left;
	t_node						*right;
	t_node						*next;
	t_node						*prev;
};
typedef struct s_global			t_global;
struct							s_global
{
	int							exit_status;
	bool						interrupt;
	int							sig;
};
typedef struct s_data_e
{
	char						**argv;
	char						**envp;
	int							rw[2];
	pid_t						pid;
	int							status;
	int atty;
}								t_data_e;
#endif
