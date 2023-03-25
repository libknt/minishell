/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:31:08 by marai             #+#    #+#             */
/*   Updated: 2023/03/25 19:51:15 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_eql(char *str)
{
	ssize_t	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

static bool	env_utils(char **argv, t_env *env, t_status *s)
{
	char	**envp;
	ssize_t	i;

	i = 0;
	s->f = true;
	if (!argv || !argv[0])
		return (true);
	else if (!argv[1])
	{
		envp = make_env_args(env);
		while (envp && envp[i] && env)
		{
			if (env->value)
				printf("%s\n", envp[i]);
			i++;
			env = env->next;
		}
		return (true);
	}
	return (false);
}

static void	env_fork(char **argv, t_env *env, t_status *s, t_node *node)
{
	char	**envp;
	ssize_t	i;
	t_env	*env_node;

	i = 1;
	while (argv[i])
	{
		if (!check_eql(argv[i]))
		{
			envp = make_env_args(env);
			s->status = execve_cmd(&argv[i], envp, node);
			exit(s->status);
		}
		env_node = new_lstenv(argv[i]);
		if (!env_node)
			_err("env_node_error\n");
		ft_env_addback(&env, env_node);
		i++;
	}
}

void	env_buildin(char *argv[], t_env *env, t_node *node, t_status *s)
{
	int	pid;
	int	status;

	if (env_utils(argv, env, s))
		return ;
	rl_event_hook = 0;
	pid = fork();
	if (pid == 0)
	{
		reset_signal();
		env_fork(argv, env, s, node);
		exit(1);
	}
	wait(&status);
	exec_action();
	s->status = status;
}
