/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:41:15 by keys              #+#    #+#             */
/*   Updated: 2023/03/10 18:50:06 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execve_simple_cmd(t_node *node, t_env *env)
{
	char	**argv;
	char	**envp;
	pid_t	pid;
	int		waitstatus;
	// t_fds	*fd;

	envp = make_env_args(env);
	redirect_adoption(node->fds);
	argv = access_cmd_path(node, envp);
	//make build in masahito
	if (buildin(argv, &env))
	{
		ft_split_free(envp);
		ft_split_free(argv);
		node->fds =revert_redirect(node->fds);
		return (1);
	}
	if (access(argv[0], X_OK))
	{
		node->fds = revert_redirect(node->fds);
		_err_cmd_node_found("command not found");
		return (1);
	}
	pid = fork();
	if (pid < 0)
		_err("fork");
	else if (pid == 0)
		execve(argv[0], argv, envp);
	wait(&waitstatus);
	node->fds = revert_redirect(node->fds);
	ft_split_free(argv);
	ft_split_free(envp);
	return (WEXITSTATUS(waitstatus));
}
