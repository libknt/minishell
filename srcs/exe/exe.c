/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:01:00 by marai             #+#    #+#             */
/*   Updated: 2023/07/01 13:02:25 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

char	**access_cmd_path(t_node *node, char **envp)
{
	char	*cmd_path;
	char	**argv;

	argv = make_arr(node);
	if (!ft_strcmp(argv[0], ".") || !ft_strcmp(argv[0], ".."))
		return (argv);
	if (!ft_strncmp(argv[0], "/", 1))
		return (argv);
	if (access(argv[0], X_OK) != 0 || !ft_strchr(argv[0], '/'))
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

static void	wait_process(void)
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
			_err_wait(status);
		}
	}
}

int	exec_tree(t_node *node, t_env **env, int atty)
{
	int	fd0;
	int	fd1;

	fd0 = dup(0);
	fd1 = dup(1);
	add_node(node);
	while (node && node->line->type == PIPE)
		node = node->left;
	add_redirect(node, *env);
	block_signal();
	while (1)
	{
		if (node->status < 1)
			exec(node, env, fd1, atty);
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	wait_process();
	exec_action();
	if (node->status == 2)
		g_global.exit_status = 0;
	dup2(fd0, 0);
	close(fd0);
	return (0);
}

int	exe_(t_node *node, t_env **env)
{
	int	atty;
	int	dummy_fd;

	dummy_fd = open("/dev/null", O_RDONLY);
	atty = isatty(1);
	if (node->line->type != PIPE)
	{
		node->fds = redirect_check(node, *env);
		if (node->status == 1)
		{
			close(dummy_fd);
			return (0);
		}
		execve_simple_cmd(node, env);
	}
	else
		exec_tree(node, env, atty);
	close(dummy_fd);
	return (0);
}
