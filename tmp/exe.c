/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marai <MasaDevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:58:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/26 23:3 by Marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 1
#define READ 0

int	exec_si(t_node *node)
{
	char		**argv;
	extern char	**environ;
	pid_t		pid;
	char		*cmd_path;
	int			waitstatus;
	int			here;

	if (node == NULL)
		return (-1);
	_redirect_si(node);
	here = here_documents(node);
	argv = NULL;
	argv = make_arr(node, here);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		if (access(argv[0], X_OK) == 0)
			execve(argv[0], argv, environ);
		else
		{
			cmd_path = exec_filename(argv[0]);
			if (cmd_path != NULL)
				execve(cmd_path, argv, environ);
			else
				_err("command not found");
		}
	}
	wait(&waitstatus);
	restore_fd(node);
	if (argv[1] && strncmp(argv[1], ".heredoc.txt", 12) == 0)
	{
		free(argv[1]);
		argv[1] = NULL;
	}
	free(argv);
	return (WEXITSTATUS(waitstatus));
}

int	t_escape_fd(int fd)
{
	int	newfd;

	newfd = fcntl(fd, F_DUPFD, 10);
	fflush(stdout);
	if (newfd < 0)
		_err("fcntl");
	if (close(fd) < 0)
		_err("close");
	return (newfd);
}

int	exec(t_node *node, int k3)
{
	char		**argv;
	extern char	**environ;
	pid_t		pid;
	char		*cmd_path;
	int			rw[2];
	int			here;

	if (!node)
		return (0);
	argv = NULL;
	_redirect_si(node);
	here = here_documents(node);
	pipe(rw);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		if (node->fd == NULL)
		{
			if (node->next == NULL)
			{
				close(rw[0]);
				close(rw[1]);
				dup2(k3, 1);
				close(k3);
			}
			else
			{
				close(rw[0]);
				dup2(rw[1], 1);
				close(rw[1]);
			}
		}
		else
		{
			close(rw[0]);
			close(rw[1]);
		}
		argv = make_arr(node, here);
		if (access(argv[0], X_OK) == 0)
			execve(argv[0], argv, environ);
		else
		{
			cmd_path = exec_filename(argv[0]);
			if (cmd_path != NULL)
				execve(cmd_path, argv, environ);
			else
				_err("command not found");
		}
		exit(0);
	}
	if (node->fd == NULL)
	{
		close(rw[1]);
		dup2(rw[0], 0);
		close(rw[0]);
	}
	else
		restore_fd(node);
	return (1);
}
/*
void	print_nodes(t_node *node)
{
	while (node)
	{
		printf("-------\n");
		printf("now %p\n", node);
		printf("next %p\n", node->next);
		node = node->next;
	}
}
*/
void	wait_process(void)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		status = 0;
		pid = wait(&status);
		if (pid == -1)
		{
			if (ECHILD == errno)
				break ;
			else if (EINTR == errno)
				continue ;
			_err("wait error");
		}
	}
}

int	exec_tree(t_node *node)
{
	int	k2;
	int	k3;

	k2 = fcntl(0, F_DUPFD, 10);
	k3 = fcntl(1, F_DUPFD, 10);
	add_node(node);
	while (node && node->line->type == PIPE)
		node = node->left;
	while (node != NULL)
	{
		exec(node, k3);
		node = node->next;
	}
	wait_process();
	dup2(k2, 0);
	close(k2);
	return (0);
}

int	exe_(t_node *node)
{
	if (node->line->type != PIPE)
		exec_si(node);
	else
		exec_tree(node);
	return (0);
}
