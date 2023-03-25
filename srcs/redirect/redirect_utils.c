/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:02:18 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 18:03:23 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*revert_redirect(t_fds *fd)
{
	if (fd == NULL)
		return (NULL);
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
	return (NULL);
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
