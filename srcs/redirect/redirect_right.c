/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:48:58 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/25 17:34:15 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_fd	*redirect_right(t_node *node, t_line *line)
{
	t_fd	*fd;

	fd = NULL;
	(void)node;
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
		else if (line->type == REDIRECT)
			line = line->next;
		line = line->next;
	}
	return (fd);
}
