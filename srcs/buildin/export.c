/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:30:45 by marai             #+#    #+#             */
/*   Updated: 2023/07/01 17:26:09 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	envp_args(char **envp, ssize_t i, t_env *env, ssize_t value_len)
{
	ssize_t	len;

	len = 0;
	len = ft_strlen(env->key) + value_len + 4;
	envp[i] = ft_calloc(len, sizeof(char));
	if (!envp[i])
		_err_malloc();
	ft_strlcat(envp[i], env->key, len);
	if (env->value)
	{
		ft_strlcat(envp[i], "=", ft_strlen(env->key) + 2);
		ft_strlcat(envp[i], "\"", ft_strlen(env->key) + 3);
		ft_strlcat(envp[i], env->value, len);
		ft_strlcat(envp[i], "\"", len);
	}
}

static char	**make_export_args(t_env *env, ssize_t i, ssize_t num,
		ssize_t value_len)
{
	char	**envp;

	num = env_num(env);
	envp = ft_calloc(num + 1, sizeof(char *));
	if (!envp)
		_err_malloc();
	while (i < num)
	{
		if (!env->value)
			value_len = 0;
		else
			value_len = ft_strlen(env->value);
		envp_args(envp, i, env, value_len);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	check_env_vari(char *argv)
{
	if (!argv)
		return (0);
	if (argv[0] == '=' || !is_identifier(argv))
	{
		ft_putstr_fd("not a valid identifier:", 2);
		ft_putendl_fd(argv, 2);
		return (0);
	}
	return (1);
}

static void	export_utils(char *argv[], t_env *env_node, t_env **env,
		t_status *s)
{
	ssize_t	i;

	i = 1;
	while (argv[i])
	{
		if (!check_env_vari(argv[i]))
		{
			i++;
			s->status = 1;
			continue ;
		}
		env_node = new_lstenv(argv[i]);
		if (!env_node)
			_err("env node error\n");
		ft_env_addback(env, env_node);
		i++;
	}
}

void	ft_export(char *argv[], t_env **env, t_status *s)
{
	ssize_t	i;
	char	**envp;

	s->f = true;
	s->status = 0;
	if (!argv[1] || !argv[1][0])
	{
		envp = make_export_args(*env, 0, 0, 0);
		envp = env_sort(envp);
		i = 0;
		while (envp[i])
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putendl_fd(envp[i], STDOUT_FILENO);
			i++;
		}
		free_envp(envp, i);
		return ;
	}
	export_utils(argv, NULL, env, s);
}
