/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_left.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:48:58 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/10 18:30:09 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	*close_file(t_fd *fd)
{
	if (fd == NULL)
		return (NULL);
	close(fd->file);
	free(fd);
	fd = NULL;
	return (NULL);
}

static t_fd	*open_file(char *name)
{
	t_fd	*new;

	new = new_fd();
	new->file = open(name, O_RDONLY, 0644);
	if (new->file < 0)
		printf("%s: No such file or directory\n", name);
	new->std_fd = 0;
	return (new);
}


t_fd	*redirect_left(t_line *line,t_env *env)
{
	t_fd	*fd;

	fd = NULL;
	while (1)
	{
		if (line->type == T_EOF_R)
			break ;
		if (line->type == REDIRECT && (!strncmp(line->token->word, "<<", 2)))
		{
			// fd = close_file(fd);
			// fd = open_file(line->next->token->word);
			fd = close_file(fd);
			line = line->next;
			fd = heredoc(line->token->word,env);
		}
		else if (line->type == REDIRECT && !strncmp(line->token->word, "<", 1))
		{
			fd = close_file(fd);
			fd = open_file(line->next->token->word);
			line = line->next;
		}
		else if (line->type == REDIRECT)
			line = line->next;
		line = line->next;
	}
	// dup_redirect(fd);
	return (fd);
}

// t_fd	*redirect_check(t_node *node)
// {
// 	t_fd	*fd;

// 	fd = redirect(node->line);
// 	return (fd);
// }

// void	revert_redirect(t_fd *fd)
// {
// 	if (fd == NULL)
// 		return ;
// 	dup2(fd->std_fd, fd->file_new);
// 	close(fd->file_new);
// 	dup2(fd->std_fd_new, fd->std_fd);
// 	close(fd->std_fd_new);
// 	close(fd->file);
// 	free(fd);
// }
