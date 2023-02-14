/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:57:25 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 17:28:59 by keys             ###   ########.fr       */
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

typedef struct s_node		t_node;
struct						s_node
{
	// t_token					*t;
	t_line					*line;
	t_node					*left;
	t_node					*right;
};
#endif
