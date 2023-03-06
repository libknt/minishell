/* ************************************************************************* */
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

static void	_err_cmd_node_found(char *mes)
{
	exit_status = 127;
	dprintf(STDERR_FILENO, "%s\n", mes);
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

static char	**access_cmd_path(t_node *node, int here)
{
	char	*cmd_path;
	char	**argv;

	argv = make_arr(node, here);
	if (access(argv[0], X_OK) == 0)
	{
	}
	else
	{
		cmd_path = exec_filename(argv[0]);
		free(argv[0]);
		argv[0] = cmd_path;
		if (cmd_path == NULL)
		{
			ft_split_free(argv);
			return (NULL);
		}
	}
	return (argv);
}

int	exec(t_node *node, t_env *env, int fd1)
{
	char		**argv;
	extern char	**environ;
	//char		**envp;
	pid_t		pid;
	int			rw[2];
	int			here;

	if (!node)
		return (0);
	argv = NULL;
	//envp = make_env_args(env);
	_redirect_si(node);
	here = here_documents(node);
	//make buold in masahito
	(void)env;
	argv = access_cmd_path(node, here);
	if (argv == NULL)
	{
		if (node->fd == NULL)
		{
			close(rw[1]);
			dup2(rw[0], 0);
			close(rw[0]);
		}
		else
			restore_fd(node);
		_err_cmd_node_found("command not found");
		//ft_split_free(envp);
		return (1);
	}
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
				dup2(fd1, 1);
				close(fd1);
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
		execve(argv[0], argv, environ);
	}
	if (node->fd == NULL)
	{
		close(rw[1]);
		dup2(rw[0], 0);
		close(rw[0]);
	}
	else
		restore_fd(node);
	ft_split_free(argv);
	//ft_split_free(envp);
	return (1);
}

void	print_nodes(t_node *node)
{
	while (node)
	{
		printf("-------\n");
		printf("now %s\n", node->line->token->word);
		printf("next %p\n", node->next);
		node = node->next;
	}
}
// #include <err.h>
// #include <errno.h>
// int	exec_tree(t_node *node, t_env *env)

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


int	exec_tree(t_node *node, t_env *env)
{
	int	fd0;
	int	fd1;

	fd0 = fcntl(0, F_DUPFD, 10);
	fd1 = fcntl(1, F_DUPFD, 10);
	add_node(node);
	while (node && node->line->type == PIPE)
		node = node->left;
	while (node != NULL)
	{
		exec(node, env, fd1);
		node = node->next;
	}
	wait_process();
	dup2(fd0, 0);
	close(fd0);
	return (0);
}

int	exe_(t_node *node, t_env *env)
{
	if (node->line->type != PIPE)
		execve_simple_cmd(node, env);
	else
		exec_tree(node, env);
	return (0);
}
