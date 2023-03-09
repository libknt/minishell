/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstenvp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:09:09 by keys              #+#    #+#             */
/*   Updated: 2023/03/09 11:26:53 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_len(char *envp)
{
	size_t	len;

	if (!envp)
		return 0;
	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	return (len);
}

void	add_env(t_env **env, char *envp, size_t len)
{
	(*env)->key = ft_substr(envp, 0, len);
	if (!env)
		_err("malloc");
}

void	add_value(t_env **env, char *envp, size_t len)
{
	if(strlen(envp) != len)
		(*env)->value = ft_substr(envp, len + 1, strlen(&envp[len + 1]));
	else
		(*env)->value = NULL;
}

t_env	*new_lstenv(char *envp)
{
	t_env	*env;
	size_t	len;

	env = calloc(sizeof(t_env), 1);
	if (!env)
		_err("calloc");
	len = env_len(envp);
	add_env(&env, envp, len);
	add_value(&env, envp, len);
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

t_env	*env_last(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_env_addback(t_env **env, t_env *new)
{
	t_env	*env_node;

	if (env)
	{
		env_node = *env;
		if (env_node)
		{
			while (env_node)
			{
				if(!strcmp(env_node->key, new->key))
				{
					env_node->prev->next = new;
					new->prev = env_node->prev;
					new->next = env_node->next;
					free(env_node);
					return ;
				}
				if (!env_node->next)
					break;
				env_node = env_node->next;
			}
			env_node->next = new;
			new->prev = env_node;
		}
		else
			*env = new;
	}
}

void	print_env(t_env *env)
{
	while (1)
	{
		if (env == NULL)
			break ;
		// printf("%s %s\n", env->key, env->value);
		env = env->next;
	}
}

void	make_lstenv(t_env **s_env, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = new_lstenv(envp[i]);
		ft_env_addback(s_env, new);
		i++;
	}
}
