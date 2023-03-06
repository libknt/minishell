/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:21:21 by keys              #+#    #+#             */
/*   Updated: 2023/03/06 10:14:45 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	line_size(t_line *line)
{
	size_t	len;

	len = 0;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == CMDLINE)
			len++;
		line = line->next;
	}
	return (len);
}

void	push_arr(char **arr, t_line *line)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == CMDLINE)
		{
			arr[i] = strdup(line->token->word);
			i++;
		}
		line = line->next;
	}
	arr[i] = NULL;
}

void	push_arr_here(char **arr, int here)
{
	char	buf[255];
	int		fd;

	fd = open(".heredoc.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	read(here, buf, 255);
	write(fd, buf, strlen(buf));
	close(fd);
	close(here);
	arr[1] = strdup(".heredoc.txt");
}

char	**make_arr(t_node *node, int here)
{
	t_line	*line;
	size_t	len;
	char	**arr;

	line = node->line;
	len = line_size(line);
	if (len == 1 && here > 0)
	{
		arr = calloc(sizeof(char **), 3);
		arr[0] = line->token->word;
		arr[2] = NULL;
		push_arr_here(arr, here);
		return (arr);
	}
	arr = calloc(sizeof(char **), len + 1);
	if (!arr)
		_err("malloc");
	push_arr(arr, line);
	return (arr);
}
