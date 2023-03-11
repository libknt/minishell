/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:58:29 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/10 19:43:59 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	*new_fds()
{
	t_fds	*new;

	new = calloc(1, sizeof(t_fds));
	if (new == NULL)
		_err("malloc");
	new->fd_r = NULL;
	new->fd_l = NULL;
	return (new);
}

t_fds	*redirect_check(t_node *node,t_env *env)
{
	t_fds	*fd;

	fd = new_fds();
	fd->fd_r = redirect_right(node->line);
	fd->fd_l = redirect_left(node->line, env);
	if (fd->fd_r == NULL && fd->fd_l == NULL)
	{
		free(fd);
		return (NULL);
	}
	return (fd);
}

void	*revert_redirect(t_fds *fd)
{
	if (fd == NULL)
		return  NULL;
	if (fd->fd_l)
	{
		dup2(fd->fd_l->std_fd, fd->fd_l->file_new);
		close(fd->fd_l->file_new);
		dup2(fd->fd_l->std_fd_new, fd->fd_l->std_fd);
		close(fd->fd_l->std_fd_new);
		close(fd->fd_l->file);
		free(fd->fd_l);
	}
	if (fd->fd_r)
	{
		dup2(fd->fd_r->std_fd, fd->fd_r->file_new);
		close(fd->fd_r->file_new);
		dup2(fd->fd_r->std_fd_new, fd->fd_r->std_fd);
		close(fd->fd_r->std_fd_new);
		close(fd->fd_r->file);
		free(fd->fd_r);
	}
	free(fd);
	return NULL;
}

void	revert_redirect_pipe(t_fds *fd, int rw[2])
{
	dup2(rw[0], 0);
	close(rw[0]);
	close(rw[1]);
	if (fd == NULL)
		return ;
	if (fd->fd_l)
	{
		dup2(fd->fd_l->std_fd, fd->fd_l->file_new);
		close(fd->fd_l->file_new);
		close(fd->fd_l->std_fd_new);
		close(fd->fd_l->file);
		free(fd->fd_l);
	}
	if (fd->fd_r)
	{
		dup2(fd->fd_r->std_fd, fd->fd_r->file_new);
		close(fd->fd_r->file_new);
		dup2(fd->fd_r->std_fd_new, fd->fd_r->std_fd);
		close(fd->fd_r->std_fd_new);
		close(fd->fd_r->file);
		free(fd->fd_r);
	}
	free(fd);
}
