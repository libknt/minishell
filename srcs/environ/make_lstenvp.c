/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstenvp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:09:09 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 00:54:58 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_addback(t_env **env, t_env *new)
{
	t_env	*env_node;

	env_node = *env;
	if (env_node)
	{
		while (env_node)
		{
			if (!strcmp(env_node->key, new->key))
			{
				env_node->prev->next = new;
				new->prev = env_node->prev;
				new->next = env_node->next;
				free(env_node);
				return ;
			}
			if (!env_node->next)
				break ;
			env_node = env_node->next;
		}
		env_node->next = new;
		new->prev = env_node;
	}
	else
		*env = new;
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
}
