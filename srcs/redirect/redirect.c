/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:58:29 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/11 20:43:09 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirect(t_node *node, t_env *env)
{
	while (node != NULL)
	{
		node->fds = redirect_check(node, env);
		node = node->next;
	}
}

t_fds	*new_fds(void)
{
	t_fds	*new;

	new = calloc(1, sizeof(t_fds));
	if (new == NULL)
		_err_malloc();
	new->fd_r = NULL;
	new->fd_l = NULL;
	return (new);
}

bool	nocmd(t_node *node)
{
	t_line	*line;

	line = node->line;
	while (1)
	{
		if (line->type == CMDLINE)
			return (false);
		else if (line->type == T_EOF_R)
			return true;
		else
			line = line->next;
	}
}

t_fds	*redirect_check(t_node *node, t_env *env)
{
	t_fds	*fd;

	fd = new_fds();
	fd->fd_l = redirect_left(node, node->line, env);
	if (node->status == 1)
	{
		free(fd);
		return (NULL);
	}
	fd->fd_r = redirect_right(node, node->line);
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
