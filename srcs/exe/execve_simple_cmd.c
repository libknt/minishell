/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:41:15 by keys              #+#    #+#             */
/*   Updated: 2023/03/06 11:11:16 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_err_cmd_node_found(char *mes)
{
	exit_status = 127;
	dprintf(STDERR_FILENO, "%s\n", mes);
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

int	execve_simple_cmd(t_node *node)
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
	argv = access_cmd_path(node, here);
	if (argv == NULL)
	{
		restore_fd(node);
		if(here)
			close(here);
		/*if (argv[1] && strncmp(argv[1], ".heredoc.txt", 12) == 0)
		{
			free(argv[1]);
			argv[1] = NULL;
		}
		free(argv);
		*/
		_err_cmd_node_found("command not found");
		return (1);
	}
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
	ft_split_free(argv);
	/*if (argv[1] && strncmp(argv[1], ".heredoc.txt", 12) == 0)
	{
		free(argv[1]);
		argv[1] = NULL;
	}
	free(argv);
	*/
	return (WEXITSTATUS(waitstatus));
}
