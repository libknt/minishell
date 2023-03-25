/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:53:32 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/25 17:21:42 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err_heredoc(char *m)
{
	printf("%s: warning: wanted `EOF'\n", m);
}

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

char	*ft_rename_dir(char *x)
{
	char	*file;
	char	*tmp;
	size_t	len;

	len = strlen(x);
	file = calloc(sizeof(char), len - 6);
	if (!file)
		_err_malloc();
	memset(file, 'x', len - 7);
	memcpy(file, x, 10);
	free(x);
	x = strdup(".heredoc");
	if (!file)
		_err("malloc");
	tmp = file;
	file = ft_strjoin(tmp, x);
	if (!file)
		_err("malloc");
	free(tmp);
	free(x);
	return (file);
}

bool	is_heredocfile(void)
{
	DIR	*d;

	d = opendir(".heredoc");
	if (d == NULL)
		return (false);
	closedir(d);
	return (true);
}
