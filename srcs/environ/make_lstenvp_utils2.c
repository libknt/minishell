/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstenvp_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:48:30 by Marai             #+#    #+#             */
/*   Updated: 2023/06/24 16:28:52 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_to_end(t_env **env_node, t_env *new)
{
	new->next = (*env_node)->next;
	(*env_node)->next = new;
	new->prev = *env_node;
}

void	ft_env_addback(t_env **env, t_env *new)
{
	t_env	*env_node;

	env_node = search_key_in_list(env, new);
	if (env_node && !ft_strcmp(env_node->key, new->key))
	{
		replace_node_in_list(env, &env_node, new);
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
