/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:58:29 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/25 11:03:07 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_redirect(t_node *node, t_env *env)
{
	while (node != NULL)
	{
		node->fds = redirect_check(node, env);
		node = node->next;
	}
}

static t_fds	*new_fds(void)
{
	t_fds	*new;

	new = ft_calloc(1, sizeof(t_fds));
	if (new == NULL)
		_err_malloc();
	new->fd_r = NULL;
	new->fd_l = NULL;
	return (new);
}

static bool	nocmd(t_node *node)
{
	t_line	*line;

	line = node->line;
	while (1)
	{
		if (line->type == CMDLINE)
			return (false);
		else if (line->type == T_EOF_R)
			return (true);
		else
			line = line->next;
	}
}

t_fds	*redirect_check(t_node *node, t_env *env)
{
	t_fds	*fd;

	fd = new_fds();
	fd->fd_l = redirect_left(node, node->line, env, NULL);
	if (node->status == 1)
	{
		free(fd);
		return (NULL);
	}
	fd->fd_r = redirect_right(node, node->line);
	if (fd->fd_r == NULL && fd->fd_l == NULL)
	{
		free(fd);
		return (NULL);
	}
	if (nocmd(node))
	{
		revert_redirect(fd);
		node->status = 1;
		return (NULL);
	}
	return (fd);
}
