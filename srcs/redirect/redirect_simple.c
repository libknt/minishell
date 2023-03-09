/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:48:58 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/09 17:23:35 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fd	*new_fd(void)
{
	t_fd	*new;

	new = calloc(1, sizeof(t_fd));
	if (new == NULL)
		_err("malloc");
	new->std_fd = -1;
	new->file = -1;
	new->file_new = -1;
	new->std_fd_new = -1;
	return (new);
}

static void	*close_file(t_fd *fd)
{
	if (fd == NULL)
		return (NULL);
	close(fd->file);
	free(fd);
	fd = NULL;
	return (NULL);
}

static t_fd	*open_file_rr(char *name)
{
	t_fd	*new;

	new = new_fd();
	new->file = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	new->std_fd = 1;
	return (new);
}
static t_fd	*open_file_r(char *name)
{
	t_fd	*new;

	new = new_fd();
	new->file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	new->std_fd = 1;
	return (new);
}

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

t_fd	*redirect(t_line *line)
{
	t_fd	*fd;

	fd = NULL;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == REDIRECT && (!strncmp(line->token->word, ">>", 2)
				|| !strncmp(line->token->word, ">", 1)))
		{
			fd = close_file(fd);
			if (!strncmp(line->token->word, ">>", 2))
				fd = open_file_rr(line->next->token->word);
			else
				fd = open_file_r(line->next->token->word);
			line = line->next;
		}
		line = line->next;
	}
	dup_redirect(fd);
	return (fd);
}

t_fd	*redirect_check(t_node *node)
{
	t_fd	*fd;

	fd = redirect(node->line);
	return (fd);
}

void	revert_redirect(t_fd *fd)
{
	if (fd == NULL)
		return ;
	dup2(fd->std_fd, fd->file_new);
	close(fd->file_new);
	dup2(fd->std_fd_new, fd->std_fd);
	close(fd->std_fd_new);
	close(fd->file);
	free(fd);
}