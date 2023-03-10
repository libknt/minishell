/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:01:20 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/10 13:01:57 by keys             ###   ########.fr       */
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

char	*rename(char *x)
{
	char	*file;

	x[0] = 'x';
	file = ft_strjoin(".", x);
	if (file == NULL)
		_err("malloc");
	free(x);
	return (file);
}

int	open_heredocfile(void)
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
			x = rename(x);
			continue ;
		}
		else
			break ;
	}
	return (fd);
}

int	heredoc_start(t_line *line)
{
	int	fd;

	fd = open_heredocfile();
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (is_heredoc(line))
		{
			line = line->next;
		}
		line = line->next;
	}
}
int	heredoc(t_node *node)
{
	heredoc_start(node->line);
}
