/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstenvp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:09:09 by keys              #+#    #+#             */
/*   Updated: 2023/06/21 16:09:50 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *search_key_in_list(t_env **env, t_env *new)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node)
	{
		if (!ft_strcmp(env_node->key, new->key))
			return env_node;
		if (!env_node->next)
			break ;
		env_node = env_node->next;
	}
	return env_node;
}

void replace_node_in_list(t_env **env_node, t_env *new)
{
	(*env_node)->prev->next = new;
	new->prev = (*env_node)->prev;
	new->next = (*env_node)->next;
	if ((*env_node)->next)
		(*env_node)->next->prev = new;
	free((*env_node)->key);
	free((*env_node)->value);
	free(*env_node);
}

void add_node_to_end(t_env **env_node, t_env *new)
{
	new->next = (*env_node)->next;
	(*env_node)->next = new;
	new->prev = *env_node;
}

void ft_env_addback(t_env **env, t_env *new)
{
	t_env	*env_node;

	env_node = search_key_in_list(env, new);
	if (env_node && !ft_strcmp(env_node->key, new->key))
	{
		replace_node_in_list(&env_node, new);
	}
	else if (env_node)
	{
		add_node_to_end(&env_node, new);
	}
	else
	{
		*env = new;
	}
}


// void	ft_env_addback(t_env **env, t_env *new)
// {
// 	t_env	*env_node;

// 	env_node = *env;
// 	if (env_node)
// 	{
// 		while (env_node)
// 		{
// 			if (!ft_strcmp(env_node->key, new->key))
// 			{
// 				env_node->prev->next = new;
// 				new->prev = env_node->prev;
// 				new->next = env_node->next;
// 				if (env_node->next)
// 					env_node->next->prev = new;
// 				free(env_node->key);
// 				free(env_node->value);
// 				free(env_node);
// 				return ;
// 			}
// 			if (!env_node->next)
// 				break ;
// 			env_node = env_node->next;
// 		}
// 		new->next = env_node->next;
// 		env_node->next = new;
// 		new->prev = env_node;
// 	}
// 	else
// 		*env = new;
// }

void	make_lstenv(t_env **s_env, char **envp)
{
	int		i;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = new_lstenv(envp[i]);
		if (s_env)
			ft_env_addback(s_env, new);
		i++;
	}
	ft_env_addback(s_env, new_lstenv("OLDPWD"));
}

t_env	*make_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		_err("malloc err\n");
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	return (new);
}
