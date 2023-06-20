/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:31:08 by marai             #+#    #+#             */
/*   Updated: 2023/06/20 15:33:10 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_env_args_utils(t_env *env, char **envp, ssize_t i,
		ssize_t value_len)
{
	ssize_t	len;

	len = ft_strlen(env->key) + value_len + 2;
	envp[i] = ft_calloc(len, sizeof(char));
	if (!envp[i])
		_err_malloc();
	ft_strlcat(envp[i], env->key, len);
	if (env->value)
	{
		ft_strlcat(envp[i], "=", ft_strlen(env->key) + 2);
		ft_strlcat(envp[i], env->value, len);
	}
}

char	**make_env_args(t_env *env)
{
	ssize_t	i;
	ssize_t	num;
	ssize_t	value_len;
	char	**envp;

	num = env_num(env);
	envp = ft_calloc(num + 1, sizeof(char *));
	if (!envp)
		_err_malloc();
	i = 0;
	while (i < num)
	{
		if (!env->value)
			value_len = 0;
		else
			value_len = ft_strlen(env->value);
		make_env_args_utils(env, envp, i, value_len);
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
