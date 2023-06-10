/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:55:38 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/10 19:23:05 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

int	command_found(char **argv, char **envp)
{
	if ((access(argv[0], X_OK) && !is_buildin(argv[0])) || is_file_access(argv[0]) )
	{
		_err_cmd_not_found(argv[0]);
		ft_split_free(envp);
		return (1);
	}
	else
		return (0);
}

void	close_pipe(t_node *node, int rw[2], int fd1)
{
	if (node->next == NULL)
	{
		close(rw[0]);
		close(rw[1]);
		if (!node->fds || (node->fds && node->fds->fd_r == NULL))
			dup2(fd1, 1);
		close(fd1);
	}
	else
	{
		close(rw[0]);
		if (!node->fds || (node->fds && node->fds->fd_r == NULL))
			dup2(rw[1], 1);
		close(rw[1]);
	}
}

int	revert_free(t_node *node, char **argv, char **envp, int rw[2])
{
	revert_redirect_pipe(node->fds, rw);
	ft_split_free(argv);
	ft_split_free(envp);
	return (1);
}

bool	check_argv(char **argv, t_node *node)
{
	if (node->prev != NULL)
	{
		if (strcmp("./minishell", argv[0]) == 0)
		{
			ft_split_free(argv);
			_err_minishell("Cannot run minishell after pipe");
			return (true);
		}
	}
	return (false);
}
