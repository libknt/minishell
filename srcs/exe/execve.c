/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marai <MasaDevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:55:38 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/13 21:22:36 by Marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	global;
static int	command_found(char **argv, char **envp)
{
	if (access(argv[0], X_OK) && !is_buildin(argv[0]))
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

static int	revert_free(t_node *node, char **argv, char **envp, int rw[2])
{
	revert_redirect_pipe(node->fds, rw);
	ft_split_free(argv);
	ft_split_free(envp);
	return (1);
}

int	exec(t_node *node, t_env *env, int fd1)
{
	char	**argv;
	char	**envp;
	int		rw[2];
	pid_t	pid;
	int		status;

	if (!node)
		return (0);
	envp = make_env_args(env);
	argv = access_cmd_path(node, envp);
	redirect_adoption(node->fds);
	if (command_found(argv, envp))
		return (1);
	pipe(rw);
	pid = fork();
	if (pid < 0)
		_err_fork();
	else if (pid == 0)
	{
		close_pipe(node, rw, fd1);
		if (is_buildin(argv[0]))
			buildin(argv, &env);
		else
			execve(argv[0], argv, envp);
	}
	if (node->next == NULL)
	{
		wait(&status);
		global.exit_status = status;
	}
	return (revert_free(node, argv, envp, rw));
}
