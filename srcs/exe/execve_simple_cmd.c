/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_simple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahitoarai <masahitoarai@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 10:41:15 by keys              #+#    #+#             */
/*   Updated: 2023/06/07 17:02:32 by masahitoara      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

int	execve_cmd(char **argv, char **envp, t_node *node)
{
	pid_t	pid;

	if (access(argv[0], X_OK))
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
	wait_process();
	exec_action();
	// g_global.exit_status = waitstatus;
	return (0);
}

int	execve_simple_cmd(t_node *node, t_env *env)
{
	char	**argv;
	char	**envp;

	envp = make_env_args(env);
	redirect_adoption(node->fds);
	argv = access_cmd_path(node, envp);
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
