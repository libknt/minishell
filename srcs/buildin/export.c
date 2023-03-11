/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:30:45 by marai             #+#    #+#             */
/*   Updated: 2023/03/12 02:20:18 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_sort(char **envp)
{
	ssize_t	i;
	ssize_t	j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i;
		while (envp[j])
		{
			if (0 < strcmp(envp[i], envp[j]))
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

char	**free_envp(char **envp, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i <= len)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}

ssize_t	env_num(t_env *env)
{
	ssize_t	num;

	num = 0;
	while (env)
	{
		num++;
		env = env->next;
	}
	return (num);
}

static char	**make_export_args(t_env *env)
{
	ssize_t	i;
	ssize_t	num;
	ssize_t	len;
	ssize_t	value_len;
	char	**envp;

	num = env_num(env);
	envp = calloc(num + 1, sizeof(char *));
	if (!envp)
		_err_malloc();
	i = 0;
	while (i < num)
	{
		if (!env->value)
			value_len = 0;
		else
			value_len = strlen(env->value);
		len = strlen(env->key) + value_len + 4;
		envp[i] = calloc(len, sizeof(char));
		if (!envp[i])
			_err_malloc();
		ft_strlcat(envp[i], env->key, len);
		if (env->value)
		{
			ft_strlcat(envp[i], "=", strlen(env->key) + 2);
			ft_strlcat(envp[i], "\"", strlen(env->key) + 3);
			ft_strlcat(envp[i], env->value, len);
			ft_strlcat(envp[i], "\"", len);
		}
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
		printf("`%s': not a valid identifier\n", argv);
		return (0);
	}
	return (1);
}

void	ft_export(char *argv[], t_env **env, t_status *s)
{
	ssize_t	i;
	char	**envp;
	t_env	*env_node;

	s->f = true;
	if (!argv[1])
	{
		envp = make_export_args(*env);
		envp = env_sort(envp);
		i = 0;
		while (envp[i])
		{
			printf("declare -x ");
			printf("%s\n", envp[i]);
			i++;
		}
		free_envp(envp, i);
		return ;
	}
	i = 1;
	while (argv[i])
	{
		if (!check_env_vari(argv[i]))
			return ;
		env_node = new_lstenv(argv[i]);
		if (!env_node)
			_err("env node error\n");
		ft_env_addback(env, env_node);
		i++;
	}
}
