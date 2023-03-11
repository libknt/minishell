/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:48:58 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/11 20:42:05 by kyoda            ###   ########.fr       */
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

static t_fd	*open_file(t_node *node, char *name)
{
	t_fd	*new;

	new = new_fd();
	new->file = open(name, O_RDONLY, 0644);
	if (new->file < 0)
		return _err_nofile(node, name);
	new->std_fd = 0;
	return (new);
}

t_fd	*redirect_left(t_node *node, t_line *line, t_env *env)
{
	t_fd	*fd;

	fd = NULL;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == REDIRECT && (!strncmp(line->token->word, "<<", 2)))
		{
			fd = close_file(fd);
			line = line->next;
			fd = heredoc(line->token->word, env);
		}
		else if (line->type == REDIRECT && !strncmp(line->token->word, "<", 1))
		{
			fd = close_file(fd);
			fd = open_file(node, line->next->token->word);
			if (fd == NULL)
				return (NULL);
			line = line->next;
		}
		else if (line->type == REDIRECT)
			line = line->next;
		line = line->next;
	}
	return (fd);
}
