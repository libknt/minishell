/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:01:20 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/10 15:28:37 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc(t_line *line)
{
	if (line->type == REDIRECT)
	{
		if (strncmp(line->token->word, "<<", 2) == 0)
			return (true);
	}
	return (false);
}

char	*ft_rename(char *x)
{
	char	*file;

	x[0] = 'x';
	file = ft_strjoin(".", x);
	if (file == NULL)
		_err("malloc");
	free(x);
	return (file);
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

void	_err_heredoc(char *m)
{
	printf("%s: warning: here-document at line 3 delimited by end-of-file (wanted `EOF')\n",
			m);
}

void	heredoc_start(int fd, char *eof,t_env *env)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			_err_heredoc("minishell");
			return ;
		}
		else if (strcmp(eof, line) == 0)
		{
			free(line);
			break ;
		}
		line = vari_expand(line, env);
		line = expand_quote(line);
		dprintf(fd, "%s\n", line);
		free(line);
	}
}
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

t_fd	*heredoc(char *eof ,t_env *env)
{
	t_fd	*new;
	char *x;

	new = new_fd();
	x= open_heredocfile(&new);
	heredoc_start(new->file, eof,env);
	new->std_fd = 0;
	close(new->file);
	new->file = open(x, O_RDONLY, 0644);
	return (new);
}
