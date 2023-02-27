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

	if (node == NULL)
		return (-1);
	argv = make_arr(node);
	////
	//_redirect(node);
	//here_documents(node);
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
		//restore_fd(node);
		///
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
	//int			waitstatus;

	if (!node)
		return 0;
	pipe(rw);
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
	{
		// if (node->left->line->type != PIPE)
		// 	_redirect(node->left);
		close(rw[0]);
		dup2(rw[1], 1);
		close(rw[1]);
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
	}
	else
	{
		//wait(&waitstatus);
		close(rw[1]);
		dup2(rw[0], 0);
		close(rw[0]);
		//return (WEXITSTATUS(waitstatus));
	}

	//_redirect(node->right);
	return (rw[0]);
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
void print_nodes(t_node *node)
{
	while (node)
	{
		printf("-------\n");
		printf("now %p\n", node);
		printf("next %p\n", node->next);
		node = node->next;
	}
}
int	exec_tree(t_node *node)
{
	
	//pid_t	pid;
	t_node *tmp;
	tmp = node;
	int		waitstatus;

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
		exec(node);
		node = node->next;
	}
	while(tmp->next != NULL)
	{
		wait(&waitstatus);
		tmp = tmp->next;
	}
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
