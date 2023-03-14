/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marai <MasaDevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:01:20 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/13 21:15:47 by Marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern t_global global;

char	*open_heredocdir(t_fd **fds)
{
	int		fd;
	char	*x;

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

void	heredoc_start(int fd, char *eof, t_env *env, t_node *node)
{
	char	*line;

	global.interrupt = 0;
	while (1)
	{
		line = readline(">");
		if(global.interrupt)
			break;
		if (line == NULL)
		{
			node->status = 2;
			write(1, "\n", 1);
			return ;
		}
		else if (strcmp(eof, line) == 0)
			break ;
		line = vari_expand(line, env);
		line = expand_quote(line);
		dprintf(fd, "%s\n", line);
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

t_fd	*heredoc(char *eof, t_env *env, t_node *node)
{
	t_fd	*new;
	char	*x;

	new = new_fd();
	if (is_heredocfile())
		x = open_heredocdir(&new);
	else
		x = open_heredocfile(&new);
	heredoc_start(new->file, eof, env, node);
	if (node->status == 1)
		return (new);
	new->std_fd = 0;
	close(new->file);
	new->file = open(x, O_RDONLY, 0644);
	free(x);
	return (new);
}
