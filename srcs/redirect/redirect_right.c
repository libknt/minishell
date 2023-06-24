/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:48:58 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/24 20:20:04 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global g_global;

static t_fd	*open_file_rr(t_node *node,char *name)
{
	t_fd	*new;

	if((access(name,F_OK) == 0) &&(access(name,W_OK) == -1))
	{
		ft_putstr_fd("minishell: ",STDERR_FILENO);
		ft_putstr_fd(name,STDERR_FILENO);
		ft_putendl_fd(": Permission denied",STDERR_FILENO);
		node->status = 1;
		g_global.exit_status = 1;
		return NULL;
	}
	new = new_fd();
	new->file = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	new->std_fd = 1;
	return (new);
}

static t_fd	*open_file_r(t_node *node,char *name)
{
	t_fd	*new;

	if((access(name,F_OK) == 0) &&(access(name,W_OK) == -1))
	{
		ft_putstr_fd("minishell: ",STDERR_FILENO);
		ft_putstr_fd(name,STDERR_FILENO);
		ft_putendl_fd(": Permission denied",STDERR_FILENO);
		node->status = 1;
		g_global.exit_status = 1;
		return NULL;
	}
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
		if (line->type == REDIRECT && (!ft_strncmp(line->token->word, ">>", 2)
				|| !ft_strncmp(line->token->word, ">", 1)))
		{
			fd = close_file(fd);
			if (!ft_strncmp(line->token->word, ">>", 2))
				fd = open_file_rr(node,line->next->token->word);
			else
				fd = open_file_r(node,line->next->token->word);
			line = line->next;
		}
		else if (line->type == REDIRECT)
			line = line->next;
		line = line->next;
	}
	return (fd);
}
