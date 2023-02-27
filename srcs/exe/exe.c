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
	int flag;

	if (node == NULL)
		return (-1);
	argv = make_arr(node);
	////
	_redirect(node,&flag);
	here_documents(node);
	//
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
		}
	}
	else
	{
		wait(&waitstatus);
		////
		restore_fd(node);
		///
		free(argv);
		return (WEXITSTATUS(waitstatus));
	}
	return (0);
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
	int here;
	here = 0;
	// int flag;

	// flag = 0;

	//int			waitstatus;
	if (!node)
		return (0);
	// _redirect(node,&flag);
	here= here_documents(node);
	pipe(rw);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		// here_documents(node);
		// if (node->left->line->type != PIPE)
		if(here)
		{
				dup2(here, 0);
				close(here);
		}
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
		//_redirect(node);
		argv = make_arr(node);
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
	else
	{
		//wait(&waitstatus);
		// k = t_escape_fd(rw[0]);
		close(rw[1]);
		// if(flag ==0)
			dup2(rw[0], 0);
		// *k1 = t_escape_fd(rw[0]);
		close(rw[0]);
	// restore_fd(node);
		//return (WEXITSTATUS(waitstatus));
	}
	close(here);
	//_redirect(node->right);
	return (1);
}

// int	exec_1(t_node *node)
// {
// 	char		**argv;
// 	extern char	**environ;
// 	char		*cmd_path;

// 	if (node == NULL)
// 		return (-1);
// 	argv = make_arr(node);
// 	if (access(argv[0], X_OK) == 0)
// 		execve(argv[0], argv, environ);
// 	else
// 	{
// 		cmd_path = exec_filename(argv[0]);
// 		if (cmd_path != NULL)
// 			execve(cmd_path, argv, environ);
// 	}
// 	return (0);
// }
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
#include <err.h>
#include <errno.h>
int	exec_tree(t_node *node)
{
	pid_t	pid;
	int		status;
	int		k2;
	int		k3;

	// int		tmp;
	// int fd3;
	// fd3= open("Makefile",O_RDONLY);
	k2 = fcntl(0, F_DUPFD, 10);
	k3 = fcntl(1, F_DUPFD, 10);
	//pid_t	pid;
	// t_node *tmp;
	// tmp = node;
	// int		waitstatus;
	// char		**argv;
	// extern char	**environ;
	// char		*cmd_path;
	// if (node == NULL)
	// 	return (-1);
	// argv = make_arr(node);
	add_node(node);
	while (node && node->line->type == PIPE)
		node = node->left;
	//print_nodes(node);
	while (node != NULL)
	{
		exec(node, k3);
		node = node->next;
	}
	// close(k1);
	// 	void	restore_fd(t_node *node)
	// {
	// 	t_fd	*_fd;
	// 	_fd = node->fd;
	// 	if (_fd == NULL)
	// 		return ;
	// 	dup2(_fd->newfd, _fd->oldfd);
	// 	close(_fd->newfd);
	// }
	// }
	// while(tmp->next != NULL)
	// {
	// 	wait(&waitstatus);
	// 	tmp = tmp->next;
	// }
	// sleep(5);
	for (;;)
	{
		status = 0;
		pid = wait(&status);
		if (pid == -1)
		{
			if (ECHILD == errno)
			{
				// 子プロセスが存在しない
				break ;
			}
			else if (EINTR == errno)
			{
				continue ;
			}
			// wait が失敗した
			err(EXIT_FAILURE, "wait error");
		}
		// (void)printf("parent: child = %d, status=%d\n", pid, status);
	}
	// sleep(5);
	dup2(k2, 0);
	close(k2);
	// sleep(5);
	(void)printf("testtest\n");
	fflush(stdout);
	// sleep(2);
	// close()
	//wait(&waitstatus);
	// // _res direct(node);
	// if (access(argv[0], X_OK) == 0)
	// 	execve(argv[0], argv, environ);
	// else
	// {
	// 	cmd_path = exec_filename(argv[0]);
	// 	if (cmd_path != NULL)
	// 		execve(cmd_path, argv, environ);
	// }
	/*
	else
	{
		wait(&waitstatus);
		return (WEXITSTATUS(waitstatus));
	}
	*/
	return (0);
}
/*
int	exec_tr(t_node *node)
{
	char		**argv;
	extern char	**environ;
	pid_t		pid;
	char		*cmd_path;
	t_node		*e;
	int			waitstatus;

	while (1)
	{
		if (node->line->type == PIPE)
		{
			if (node->right)
			{
				e = node->right;
				_redirect(e);
				here_documents(e);
				argv = make_arr(e);
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
					}
				}
				else
				{
					wait(&waitstatus);
					restore_fd(e);
					free(argv);
					// return (WEXITSTATUS(waitstatus));
				}
			}
		}
		else
		{
			pid = fork();
		}
		node = node->left;
	}
	argv = make_arr(node);
	////
	//
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
		}
	}
	else
	{
		wait(&waitstatus);
		////
		restore_fd(node);
		///
		free(argv);
		return (WEXITSTATUS(waitstatus));
	}
	return (0);
}
*/
int	exe_(t_node *node)
{
	if (node->line->type != PIPE)
		exec_si(node);
	else
	{
		exec_tree(node);
	}
	return (0);
}

// void	exec_tree(t_node *node)
// {
// 	int		rw[2];
// 	int		rw1[2];
// 	pid_t	pid;

// 	//int wstatus;
// 	if (!node)
// 		return ;
// 	pid = fork();
// 	pipe(rw);
// 	if (pid == 0)
// 	{
// 		close(READ);
// 		dup2(rw[WRITE], 1);
// 		close(rw[WRITE]);
// 		pid = fork();
// 		exec(node->left);
// 		sleep(2);
// 		return ;
// 		// sleep(1);
// 		// close(rw[WRITE]);
// 		// dup2(rw[READ], 0);
// 		// close(rw[READ]);
// 		// exec_1(node->right);
// 		// return ;
// 	}
// 	else
// 	{
// 	}
// }

// int	exe(t_node *node)
// {
// 	char		**argv;
// 	extern char	**environ;
// 	pid_t		pid;
// 	char		*cmd_path;
// 	int			waitstatus;

// 	argv = make_arr(node);
// 	here_documents(node);
// 	// _redirect(node);
// 	printf("-------------------------------------\n");
// 	fflush(stdout);
// 	pid = fork();
// 	if (pid < 0)
// 		_err("fork");
// 	else if (pid == 0)
// 	{
// 		if (access(argv[0], X_OK) == 0)
// 			execve(argv[0], argv, environ);
// 		else
// 		{
// 			cmd_path = exec_filename(argv[0]);
// 			if (cmd_path != NULL)
// 				execve(cmd_path, argv, environ);
// 		}
// 		_err("execve: command not found");
// 	}
// 	else
// 	{
// 		wait(&waitstatus);
// 		restore_fd(node);
// 		free(argv);
// 		return (WEXITSTATUS(waitstatus));
// 	}
// 	return (0);
// }

// int	exe_tree(t_node *node)
// {
// 	char		**argv;
// 	extern char	**environ;
// 	char		*cmd_path;
// 	int			rw[2];
// 	pid_t		pid;
// 	int			waitstatus;

// 	if (node->left && (node->left->left == NULL))
// 	{
// 		pipe(rw);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			argv = make_arr(node->left);
// 			dup2(rw[WRITE], 1);
// 			close(rw[1]);
// 			close(rw[0]);
// 			if (access(argv[0], X_OK) == 0)
// 				execve(argv[0], argv, environ);
// 			else
// 			{
// 				cmd_path = exec_filename(argv[0]);
// 				if (cmd_path != NULL)
// 					execve(cmd_path, argv, environ);
// 			}
// 			_err("execve: command not found");
// 		}
// 		else
// 		{
// 			wait(&waitstatus);
// 			restore_fd(node);
// 			free(argv);
// 			return (WEXITSTATUS(waitstatus));
// 		}
// 	}
// }

// int	exe(t_node *node)
// {
// 	char		**argv;
// 	extern char	**environ;
// 	pid_t		pid;
// 	char		*cmd_path;
// 	int			waitstatus;

// 	argv = make_arr(node);
// 	// here_documents(node);
// 	// _redirect(node);
// 	printf("-------------------------------------\n");
// 	fflush(stdout);
// 	pid = fork();
// 	if (pid < 0)
// 		_err("fork");
// 	else if (pid == 0)
// 	{
// 		if (access(argv[0], X_OK) == 0)
// 			execve(argv[0], argv, environ);
// 		else
// 		{
// 			cmd_path = exec_filename(argv[0]);
// 			if (cmd_path != NULL)
// 				execve(cmd_path, argv, environ);
// 		}
// 		_err("execve: command not found");
// 	}
// 	else
// 	{
// 		wait(&waitstatus);
// 		restore_fd(node);
// 		free(argv);
// 		return (WEXITSTATUS(waitstatus));
// 	}
// 	return (0);
// }

// int	exe(t_node *node)
// {
// 	int			rw[2];
// 	char		**argv;
// 	extern char	**environ;
// 	pid_t		pid;
// 	char		*cmd_path;
// 	int			waitstatus;

// 	if (node->left)
// 	{
// 		exe(node->left);
// 		pipe(rw);
// 		pid = fork();
// 		if (pid < 0)
// 			_err("fork");
// 		else if (pid == 0)
// 		{
// 			argv = make_arr(node->left);
// 			close(rw[0]);
// 			dup2(rw[1], 1);
// 			close(rw[1]);
// 			if (access(argv[0], X_OK) == 0)
// 				execve(argv[0], argv, environ);
// 			else
// 			{
// 				cmd_path = exec_filename(argv[0]);
// 				if (cmd_path != NULL)
// 					execve(cmd_path, argv, environ);
// 			}
// 			_err("execve: command not found");
// 		}
// 		else
// 		{
// 			wait(&waitstatus);
// 			dup2(rw[0], 0);
// 			close(rw[1]);
// 			close(rw[0]);
// 			// restore_fd(node);
// 			return (WEXITSTATUS(waitstatus));
// 		}
// 	}
// 	// exe(node);
// 	return (0);
// }
