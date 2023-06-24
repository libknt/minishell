/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstenvp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:09:09 by keys              #+#    #+#             */
/*   Updated: 2023/06/24 20:06:20 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*search_key_in_list(t_env **env, t_env *new)
{
	t_env	*env_node;

	env_node = *env;

	while (env_node)
	{
		if (!ft_strcmp(env_node->key, new->key))
			return (env_node);
		if (!env_node->next)
			break ;
		env_node = env_node->next;
	}
	return (env_node);
}

void	replace_node_in_list(t_env **head, t_env **env_node, t_env *new)
{
	t_env	*tmp;

	if (!new->value)
	{
		free(new->key);
		free(new->value);
		free(new);
		return ;
	}
	tmp = *env_node;
	if (tmp->prev)
		tmp->prev->next = new;
	else
		(*head) = new;
	new->prev = tmp->prev;
	new->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = new;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
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
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
