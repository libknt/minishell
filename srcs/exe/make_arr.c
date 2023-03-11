/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:21:21 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 21:38:33 by kyoda            ###   ########.fr       */
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
			if (!arr[i])
				_err_malloc();
			i++;
		}
		line = line->next;
	}
	arr[i] = NULL;
}

char	**make_arr(t_node *node)
{
	t_line	*line;
	size_t	len;
	char	**arr;

	line = node->line;
	len = line_size(line);
	arr = calloc(sizeof(char **), len + 1);
	if (!arr)
		_err_malloc();
	push_arr(arr, line);
	return (arr);
}
