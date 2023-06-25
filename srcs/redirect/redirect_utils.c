/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:02:18 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:04:23 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	revert_fd_r(t_fd *fd_r)
{
	if (fd_r == NULL)
		return ;
	dup2(fd_r->std_fd, fd_r->file_new);
	close(fd_r->file_new);
	dup2(fd_r->std_fd_new, fd_r->std_fd);
	close(fd_r->std_fd_new);
	close(fd_r->file);
	free(fd_r);
}

static void	revert_fd_l(t_fd *fd_l, bool flag)
{
	if (fd_l == NULL)
		return ;
	if (fd_l->filelinks)
	{
		unlink(fd_l->filelinks);
		free(fd_l->filelinks);
		fd_l->filelinks = NULL;
	}
	dup2(fd_l->std_fd, fd_l->file_new);
	close(fd_l->file_new);
	if (flag)
		dup2(fd_l->std_fd_new, fd_l->std_fd);
	close(fd_l->std_fd_new);
	close(fd_l->file);
	free(fd_l);
}

void	*revert_redirect(t_fds *fd)
{
	if (fd == NULL)
		return (NULL);
	revert_fd_r(fd->fd_r);
	revert_fd_l(fd->fd_l, true);
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
	revert_fd_r(fd->fd_r);
	revert_fd_l(fd->fd_l, false);
	free(fd);
}
