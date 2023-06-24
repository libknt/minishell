/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:53:32 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/23 12:13:50 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err_heredoc(char *m)
{
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": warning: wanted `EOF'", STDERR_FILENO);
}

bool	is_heredoc(t_line *line)
{
	if (line->type == REDIRECT)
	{
		if (ft_strncmp(line->token->word, "<<", 2) == 0)
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

	len = ft_strlen(x);
	file = ft_calloc(sizeof(char), len - 6);
	if (!file)
		_err_malloc();
	ft_memset(file, 'x', len - 7);
	ft_memcpy(file, x, 10);
	free(x);
	x = ft_strdup(".heredoc");
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
