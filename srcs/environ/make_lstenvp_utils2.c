/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_lstenvp_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 00:48:30 by Marai             #+#    #+#             */
/*   Updated: 2023/06/25 13:02:34 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_skip(char c, int *status)
{
	if (c == '\'' && *status == NO_QUOTE)
		*status = SINGLE_QUOTE;
	else if (c == '\'' && *status == SINGLE_QUOTE)
		*status = NO_QUOTE;
	else if (c == '"' && *status == NO_QUOTE)
		*status = DOUBLE_QUOTE;
	else if (c == '"' && *status == DOUBLE_QUOTE)
		*status = NO_QUOTE;
	else
		return (false);
	return (true);
}

static void	add_node_to_end(t_env **env, t_env *new)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node && env_node->next)
		env_node = env_node->next;
	if (env_node)
	{
		env_node->next = new;
		new->prev = env_node;
	}
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
		add_node_to_end(env, new);
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
