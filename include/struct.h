/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:57:25 by keys              #+#    #+#             */
/*   Updated: 2023/03/09 16:08:07 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_fd			t_fd;
struct						s_fd
{
	int						std_fd;
	int						file;
	int						file_new;
	int						std_fd_new;
};

typedef enum e_token_type	t_token_type;
enum						e_token_type
{
	WORD,
	RESERVED,
	OP,
	T_EOF,
};

typedef struct s_token		t_token;
struct						s_token
{
	t_token					*next;
	t_token_type			type;
	char					*word;
};

typedef struct s_data_t		t_data_t;
struct						s_data_t
{
	ssize_t					len;
	size_t					i;
	bool					sq;
	bool					dq;
	t_token					*head;
	t_token					*token;
	char					*word;
	char					*prompt;
};

typedef struct s_env		t_env;
struct						s_env
{
	char					*key;
	char					*value;
	t_env					*prev;
	t_env					*next;
};

typedef enum e_redirect		t_redirect;
enum						e_redirect
{
	PIPE,
	CMDLINE,
	REDIRECT,
	FILENAME,
	T_EOF_R,
};

typedef struct s_line		t_line;
struct						s_line
{
	t_redirect				type;
	t_token					*token;
	t_line					*next;
};

typedef struct s_node		t_node;
struct						s_node
{
	t_line					*line;
	t_node					*left;
	t_node					*right;
	t_node					*next;
};
#endif
