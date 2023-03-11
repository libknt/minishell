/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <masadevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:01:00 by marai             #+#    #+#             */
/*   Updated: 2023/03/10 01:01:17 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define WRITE 1
#define READ 0

extern int	exit_status;

static void	_err_cmd_node_found(char *mes)
{
	exit_status = 127;
	dprintf(STDERR_FILENO, "%s\n", mes);
}

static char	**access_cmd_path(t_node *node, char **envp)
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

int	exec(t_node *node, t_env *env, int fd1)
{
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		rw[2];

	if (!node)
		return (0);
	envp = make_env_args(env);
	argv = access_cmd_path(node, envp);
 
	redirect_adoption(node->fds);
	pipe(rw);
	//make buold in masahito
	if (access(argv[0], X_OK) && !is_buildin(argv[0]))
	{
		close(rw[1]);
		dup2(rw[0], 0);
		close(rw[0]);
		_err_cmd_node_found("command not found");
		ft_split_free(envp);
		return (1);
	}
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
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
		if (is_buildin(argv[0]))
			buildin(argv, &env);
		else
			execve(argv[0], argv, envp);
		exit(1);
	}
	revert_redirect_pipe(node->fds, rw);
	ft_split_free(argv);
	ft_split_free(envp);
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

void add_redirect(t_node *node,t_env *env)
{
	while (node != NULL)
	{
		node->fds = redirect_check(node,env);
		node = node->next;
	}
}

int	exec_tree(t_node *node, t_env *env)
{
	int	fd0;
	int	fd1;

	//fd0 = fcntl(0, F_DUPFD, 10);
	//fd1 = fcntl(1, F_DUPFD, 10);
	fd0 = dup(0);
	fd1 = dup(1);
	add_node(node);
	while (node && node->line->type == PIPE)
		node = node->left;
	add_redirect(node,env);
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
		node->fds = redirect_check(node,env);
		execve_simple_cmd(node, env);
	}
	else
		exec_tree(node, env);
	return (0);
}
