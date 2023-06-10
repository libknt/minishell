/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:01:20 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/10 20:34:09 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	*open_heredocdir(t_fd **fds)
{
	int		fd;
	char	*x;

	int dummy_fd;
	dummy_fd = open("/dev/null", O_RDONLY);
	x = strdup(".heredoc/.x.heredoc");
	if (x == NULL)
		_err("malloc");
	while (1)
	{
		fd = open(x, O_EXCL | O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
		{
			x = ft_rename_dir(x);
			continue ;
		}
		else
			break ;
	}
	(*fds)->file = fd;
	close(dummy_fd);
	return (x);

}

char	*open_heredocfile(t_fd **fds)
{
	int		fd;
	char	*x;

	x = strdup(".x.heredoc");
	if (x == NULL)
		_err("malloc");
	while (1)
	{
		fd = open(x, O_EXCL | O_CREAT | O_WRONLY, 0644);
		if (fd < 0)
		{
			x = ft_rename(x);
			continue ;
		}
		else
			break ;
	}
	(*fds)->file = fd;
	return (x);
}

void	heredoc_start(t_heredoc_var *v, t_env *env, t_node *node)
{
	char	*line;

	g_global.interrupt = 0;
	while (1)
	{
		line = readline(">");
		if (g_global.interrupt)
			break ;
		if (line == NULL)
		{
			node->status = 2;
			write(1, "\n", 1);
			return ;
		}
		else if (strcmp(v->eof, line) == 0)
			break ;
		if (v->flag == false)
			line = vari_expand(line, env);
		dprintf(v->fd, "%s\n", line);
		free(line);
	}
	free(line);
}

static t_fd	*new_fd(void)
{
	t_fd	*new;

	new = calloc(1, sizeof(t_fd));
	if (new == NULL)
		_err_malloc();
	new->std_fd = -1;
	new->file = -1;
	new->file_new = -1;
	new->std_fd_new = -1;
	return (new);
}

t_fd	*heredoc(t_heredoc_var *v, t_env *env, t_node *node)
{
	t_fd	*new;
	char	*x;

	new = new_fd();
	if (is_heredocfile())
		x = open_heredocdir(&new);
	else
		x = open_heredocfile(&new);
	v->fd = new->file;
	heredoc_start(v, env, node);
	if (node->status == 1)
		return (new);
	new->std_fd = 0;
	close(new->file);
	new->file = open(x, O_RDONLY, 0644);
	if (new->file < 0)
	{
		write(1, "Do not delete heredoc files!\n", 29);
		node->status = 1;
		return (NULL);
	}
	free(x);
	return (new);
}
