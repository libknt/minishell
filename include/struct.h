/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:57:25 by keys              #+#    #+#             */
/*   Updated: 2023/02/25 16:53:52 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_fd			t_fd;
struct						s_fd
{
	int						fd;
	int						oldfd;
	int						newfd;
};

typedef struct s_node		t_node;
struct						s_node
{
	t_fd					*fd;
	t_line					*line;
	t_node					*left;
	t_node					*right;
};
#endif
