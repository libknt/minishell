/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:01:00 by marai             #+#    #+#             */
/*   Updated: 2023/03/11 17:24:47 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err_cmd_node_found(char *mes)
{
	dprintf(STDERR_FILENO, "%s\n", mes);
}

char	**access_cmd_path(t_node *node, char **envp)
{
	char	*cmd_path;
	char	**argv;

	argv = make_arr(node);
	if (access(argv[0], X_OK) != 0)
	{
		cmd_path = NULL;
		if (!is_buildin(argv[0]))
			cmd_path = exec_filename(argv[0], envp);
		if (cmd_path != NULL)
		{
			free(argv[0]);
			argv[0] = cmd_path;
		}
	}
	return (argv);
}

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

	fd0 = dup(0);
	fd1 = dup(1);
	add_node(node);
	while (node && node->line->type == PIPE)
		node = node->left;
	add_redirect(node, env);
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
	{
		node->fds = redirect_check(node, env);
		execve_simple_cmd(node, env);
	}
	else
		exec_tree(node, env);
	return (0);
}
