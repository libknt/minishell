/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 16:54:43 by keys              #+#    #+#             */
/*   Updated: 2023/02/28 16:59:17 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// // static void	print_fd(t_fd *fd)
// // {
// // 	while (1)
// // 	{
// // 		printf("new = %d\n", fd->newfd);
// // 		printf("old = %d\n", fd->oldfd);
// // 		printf("fd  = %d\n", fd->fd);
// // 	}
// // }

// t_fd	*newfd(int fd, int oldfd)
// {
// 	t_fd	*new;

// 	new = calloc(sizeof(t_fd), 1);
// 	if (!new)
// 		_err("malloc");
// 	new->fd = fd;
// 	new->oldfd = oldfd;
// 	return (new);
// }

// static void	new_fd_num(t_line *line, int *fd, int *oldfd)
// {
// 	if (strncmp(line->token->word, ">>", 2) == 0)
// 	{
// 		*fd = open(line->next->token->word, O_CREAT | O_WRONLY | O_APPEND,
// 				0644);
// 		*oldfd = 1;
// 	}
// 	else if (strncmp(line->token->word, ">", 1) == 0)
// 	{
// 		*fd = open(line->next->token->word, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 		*oldfd = 1;
// 	}
// 	else if (strncmp(line->token->word, "<", 1) == 0)
// 	{
// 		*fd = open(line->next->token->word, O_RDONLY, 0644);
// 		*oldfd = 0;
// 	}
// }

// static int	escape_fd(int fd)
// {
// 	int	newfd;

// 	newfd = fcntl(fd, F_DUPFD, 10);
// 	fflush(stdout);
// 	if (newfd < 0)
// 		_err("fcntl");
// 	if (close(fd) < 0)
// 		_err("close");
// 	return (newfd);
// }

// static void	make_fd_struct_r(t_node *node, t_line *line)
// {
// 	int		fd;
// 	int		oldfd;
// 	t_fd	*_fd;

// 	node->fd = NULL;
// 	while (1)
// 	{
// 		if (line->type == T_EOF_R)
// 			break ;
// 		else if (line->type == REDIRECT)
// 		{
// 			if (strncmp(line->token->word, "<<", 2) == 0)
// 			{
// 				line = line->next->next;
// 				continue ;
// 			}
// 			if (node->fd != NULL)
// 			{
// 				dup2(_fd->newfd, _fd->oldfd);
// 				close(_fd->newfd);
// 				free(_fd);
// 				node->fd = NULL;
// 				_fd = NULL;
// 			}
// 			new_fd_num(line, &fd, &oldfd);
// 			_fd = newfd(fd, oldfd);
// 			_fd->fd = escape_fd(_fd->fd);
// 			_fd->newfd = escape_fd(_fd->oldfd);
// 			node->fd = _fd;
// 			line = line->next->next;
// 			continue ;
// 		}
// 		line = line->next;
// 	}
// }

// int	_redirect(t_node *node)
// {
// 	t_fd	*_fd;

// 	make_fd_struct_r(node, node->line);
// 	if (node->fd == NULL)
// 		return 0;
// 	_fd = node->fd;
// 	if (_fd->oldfd != _fd->fd)
// 	{
// 		dup2(_fd->fd, _fd->oldfd);
// 		close(_fd->fd);
// 	}
// 	return 0;
// }

// void	restore_fd(t_node *node)
// {
// 	t_fd	*_fd;

// 	_fd = node->fd;
// 	if (_fd == NULL)
// 		return ;
// 	dup2(_fd->newfd, _fd->oldfd);
// 	close(_fd->newfd);
// }
