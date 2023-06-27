/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstenvp_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahito <masahito@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:48:30 by Marai             #+#    #+#             */
/*   Updated: 2023/06/27 00:36:51 by masahito         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	environ_len(char *envp)
{
	size_t	len;

	if (!envp)
		return (0);
	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	return (len);
}

static void	add_env(t_env **env, char *envp, size_t len)
{
	(*env)->key = ft_substr(envp, 0, len);
	if (!env || !(*env)->key)
		_err("malloc");
}

static void	add_value(t_env **env, char *envp, size_t len)
{
	if (ft_strlen(envp) != len)
	{
		(*env)->value = ft_substr(envp, len + 1, ft_strlen(&envp[len + 1]));
		if (!(*env)->value)
			_err_malloc();
	}
	else
		(*env)->value = NULL;
}

t_env	*new_lstenv(char *envp)
{
	t_env	*env;
	size_t	len;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		_err_malloc();
	len = environ_len(envp);
	add_env(&env, envp, len);
	add_value(&env, envp, len);
	env->prev = NULL;
	env->next = NULL;
	return (env);
}
