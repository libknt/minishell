/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:55:38 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/21 15:47:13 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	exec_fork(t_node *node, t_env *env, int fd1, t_data_e *d)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		_err_fork();
	else if (pid == 0)
	{
		reset_signal();
		close_pipe(node, d->rw, fd1);
		if (is_buildin(d->argv[0]))
			buildin(d->argv, &env, node);
		else
			execve(d->argv[0], d->argv, d->envp);
	}
	return (pid);
}

int	exec(t_node *node, t_env *env, int fd1, int atty)
{
	t_data_e	d;
	int			pid;

	ft_memset(&d, 0, sizeof(t_data_e));
	if (!node)
		return (0);
	d.envp = make_env_args(env);
	d.argv = access_cmd_path(node, d.envp);
	d.atty = atty;
	redirect_adoption(node->fds);
	if (command_found(d.argv, d.envp))
		return (1);
	if (check_argv(d.argv, node))
		return (0);
	pipe(d.rw);
	rl_event_hook = 0;
	pid = exec_fork(node, env, fd1, &d);
	if (node->next == NULL)
	{
		waitpid(pid, &(d.status), 0);
		g_global.exit_status = d.status;
	}
	return (revert_free(node, d.argv, d.envp, d.rw));
}
