/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_adoption.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:29:09 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:04:14 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	escape(int fd)
{
	int	newfd;
	int	dummy_fd;

	dummy_fd = open("/dev/null", O_RDONLY);
	newfd = dup(fd);
	if (newfd < 0)
		_err("dup");
	if (close(fd) < 0)
		_err("close");
	close(dummy_fd);
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
