/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <masadevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:31:08 by marai             #+#    #+#             */
/*   Updated: 2023/03/10 00:31:10 by marai            ###   ########.fr       */
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

char	**make_env_args(t_env *env)
{
	ssize_t	i;
	ssize_t	num;
	ssize_t	len;
	ssize_t	value_len;
	char	**envp;

	num = env_num(env);
	envp = calloc(num + 1, sizeof(char *));
	i = 0;
	while (i < num)
	{
		if (!env->value)
			value_len = 0;
		else
			value_len = strlen(env->value);
		len = strlen(env->key) + value_len + 2;
		envp[i] = calloc(len, sizeof(char));
		if (!envp[i])
			return (free_envp(envp, i));
		ft_strlcat(envp[i], env->key, len);
		if (env->value)
		{
			ft_strlcat(envp[i], "=", strlen(env->key) + 2);
			ft_strlcat(envp[i], env->value, len);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	env_buildin(char *argv[], t_env *env)
{
	char	**envp;
	int		pid;
	int		status;
	t_env	*env_node;
	ssize_t	i;

	i = 0;
	if (!argv || !argv[0])
		return ;
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
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		i = 1;
		while (argv[i])
		{
			if (check_eql(argv[i]))
				_err("invalid error\n");
			env_node = new_lstenv(argv[i]);
			if (!env_node)
				_err("env_node_error\n");
			ft_env_addback(&env, env_node);
			i++;
		}
		exit(1);
	}
	else
		wait(&status);
}
