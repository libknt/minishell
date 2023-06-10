/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:41:15 by keys              #+#    #+#             */
/*   Updated: 2023/06/10 19:16:37 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

int	execve_cmd(char **argv, char **envp, t_node *node)
{
	pid_t	pid;
	int waitstatus;
	
	if (access(argv[0], X_OK) || is_file_access(argv[0]))
	{
		node->fds = revert_redirect(node->fds);
		_err_cmd_not_found(argv[0]);
		return (-2);
	}
	rl_event_hook = 0;
	pid = fork();
	if (pid < 0)
		_err_fork();
	else if (pid == 0)
	{
		reset_signal();
		execve(argv[0], argv, envp);
	}
	// wait_process();
	waitpid(pid, &waitstatus, 0); 
	g_global.exit_status = waitstatus;
	exec_action();
	return (0);
}

int	execve_simple_cmd(t_node *node, t_env *env)
{
	char	**argv;
	char	**envp;

	envp = make_env_args(env);
	redirect_adoption(node->fds);
	argv = access_cmd_path(node, envp);
	fflush(stdout);
	if (buildin_simple(argv, &env, node))
	{
		ft_split_free(envp);
		ft_split_free(argv);
		node->fds = revert_redirect(node->fds);
		return (0);
	}
	if (execve_cmd(argv, envp, node) < 0)
		return (1);
	node->fds = revert_redirect(node->fds);
	ft_split_free(argv);
	ft_split_free(envp);
	return (0);
}
