/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:58:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/26 13:53:46 by keys             ###   ########.fr       */
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

	if (node == NULL)
		return (-1);
	argv = make_arr(node);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		// _redirect(node);
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
		free(argv);
		return (WEXITSTATUS(waitstatus));
	}
	return (0);
}

int	exec(t_node *node)
{
	char		**argv;
	extern char	**environ;
	pid_t		pid;
	char		*cmd_path;
	int			rw[2];
	int			waitstatus;

	// argv = make_arr(node);
	pipe(rw);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		close(rw[0]);
		dup2(rw[1], 1);
		close(rw[1]);
		if (node->left->line->type == PIPE)
			exec(node->left);
		else
		{
			argv = make_arr(node->left);
			// _redirect(node);
			if (access(argv[0], X_OK) == 0)
				execve(argv[0], argv, environ);
			else
			{
				cmd_path = exec_filename(argv[0]);
				if (cmd_path != NULL)
					execve(cmd_path, argv, environ);
			}
		}
	}
	else
	{
		// wait()
		wait(&waitstatus);
		// sleep(1);
		close(rw[1]);
		dup2(rw[0], 0);
		close(rw[0]);
		argv = make_arr(node->right);
		// _redirect(node);
		if (access(argv[0], X_OK) == 0)
			execve(argv[0], argv, environ);
		else
		{
			cmd_path = exec_filename(argv[0]);
			if (cmd_path != NULL)
				execve(cmd_path, argv, environ);
		}
		return (WEXITSTATUS(waitstatus));
	}
	return (0);
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

int	exec_tree(t_node *node)
{
	pid_t	pid;
	int		waitstatus;

	// char		**argv;
	// extern char	**environ;
	// char		*cmd_path;
	// if (node == NULL)
	// 	return (-1);
	// argv = make_arr(node);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		exec(node);
		// // _redirect(node);
		// if (access(argv[0], X_OK) == 0)
		// 	execve(argv[0], argv, environ);
		// else
		// {
		// 	cmd_path = exec_filename(argv[0]);
		// 	if (cmd_path != NULL)
		// 		execve(cmd_path, argv, environ);
		// }
	}
	else
	{
		wait(&waitstatus);
		return (WEXITSTATUS(waitstatus));
	}
	return (0);
}

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
