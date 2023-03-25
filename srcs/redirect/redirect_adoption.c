/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_adoption.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:29:09 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 17:33:10 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	escape(int fd)
{
	int	newfd;

	newfd = fcntl(fd, F_DUPFD, 10);
	if (newfd < 0)
		_err("fcntl");
	if (close(fd) < 0)
		_err("close");
	return (newfd);
}

static void	dup_redirect(t_fd *fd)
{
	if (fd == NULL)
		return ;
	fd->std_fd_new = escape(fd->std_fd);
	fd->file_new = escape(fd->file);
	if (fd->file_new != fd->std_fd)
		dup2(fd->file_new, fd->std_fd);
	close(fd->file_new);
}

void	redirect_adoption(t_fds *fds)
{
	if (fds == NULL)
		return ;
	dup_redirect(fds->fd_l);
	dup_redirect(fds->fd_r);
}
