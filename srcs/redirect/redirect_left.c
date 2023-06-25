/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:48:58 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/25 13:04:17 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	*close_file(t_fd *fd)
{
	if (fd == NULL)
		return (NULL);
	close(fd->file);
	if (fd->filelinks)
	{
		unlink(fd->filelinks);
		free(fd->filelinks);
		fd->filelinks = NULL;
	}
	free(fd);
	fd = NULL;
	return (NULL);
}

static t_fd	*open_file(t_node *node, char *name)
{
	t_fd	*new;

	if ((access(name, F_OK) == 0) && (access(name, R_OK) == -1))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(name, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
		node->status = 1;
		g_global.exit_status = 1;
		return (NULL);
	}
	new = new_fd();
	new->file = open(name, O_RDONLY, 0644);
	if (new->file < 0)
	{
		free(new);
		return (_err_nofile(node, name));
	}
	new->std_fd = 0;
	return (new);
}

static t_fd	*redirect_left_utils(t_node *node, t_line **line, t_fd *fd,
		t_env *env)
{
	t_heredoc_var	v;

	fd = close_file(fd);
	v.flag = false;
	*line = (*line)->next;
	v.eof = (*line)->token->word;
	v.flag = (*(*line)->token->ex_heredoc_flag);
	fd = heredoc(&v, env, node);
	if (node->status == 1)
	{
		fd = close_file(fd);
		return (NULL);
	}
	return (fd);
}

t_fd	*redirect_left(t_node *node, t_line *line, t_env *env, t_fd *fd)
{
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == REDIRECT && (!ft_strncmp(line->token->word, "<<", 2)))
		{
			fd = redirect_left_utils(node, &line, fd, env);
			if (fd == NULL)
				return (NULL);
		}
		else if (line->type == REDIRECT && !ft_strncmp(line->token->word, "<",
				1))
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
