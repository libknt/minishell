/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:11:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/24 00:01:18 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	*newfd(int fd)
{
	t_fd	*new;

	new = calloc(sizeof(t_fd), 1);
	if (!new)
		_err("malloc");
	new->prev = NULL;
	new->next = NULL;
	new->fd = fd;
	return (new);
}

t_fd	*fd_last(t_fd **fd)
{
	t_fd	*tmp;

	tmp = *fd;
	while (1)
	{
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	fd_addback(t_fd **fd_, t_fd *new)
{
	t_fd	*last;

	if (fd_)
	{
		if (*fd_)
		{
			last = fd_last(fd_);
			last->next = new;
			new->prev = last;
		}
		else
		{
			*fd_ = new;
		}
	}
}

int	new_fd_num(t_line *line)
{
	int	fd;

	// else if (strncmp(line->token->word, "<<", 2) == 0)
	// 	fd = open(line->next->token->word, O_CREAT | O_RDONLY | O_APPEND, 0644);
	if (strncmp(line->token->word, ">>", 2) == 0)
		fd = open(line->next->token->word, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (strncmp(line->token->word, ">", 1) == 0)
		fd = open(line->next->token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (strncmp(line->token->word, "<", 1) == 0)
		fd = open(line->next->token->word, O_RDONLY, 0644);
	return (fd);
}

void	make_fd_struct_r(t_node *node, t_line *line)
{
	int		new_fd;
	t_fd	*_fd;

	node->fd = NULL;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == REDIRECT)
		{
			new_fd = new_fd_num(line);
			_fd = newfd(new_fd);
			fd_addback(&node->fd, _fd);
			line = line->next;
		}
		line = line->next;
	}
}

void	_redirect(t_node *node)
{
	t_fd	*_fd;
	int		oldfd;

	oldfd = 0;
	make_fd_struct_r(node, node->line);
	_fd = node->fd;
	while (1)
	{
		if (_fd == NULL)
			break ;
		if (oldfd != _fd->fd)
		{
			dup2(_fd->fd, oldfd);
		}
		_fd = _fd->next;
	}
}
