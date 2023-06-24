/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:36:46 by marai             #+#    #+#             */
/*   Updated: 2023/06/24 21:05:37 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env(char *arg, t_env **env)
{
	t_env	*env_node;

	env_node = *env;
	while (env_node)
	{
		if (!ft_strcmp(arg, env_node->key))
		{
			if (env_node->prev)
				env_node->prev->next = env_node->next;
			else
				*env = env_node->next;
			if (env_node->next)
				env_node->next->prev = env_node->prev;
			free(env_node->key);
			free(env_node->value);
			free(env_node);
			break ;
		}
		env_node = env_node->next;
	}
}

void	unset(char *argv[], t_env **env, t_status *s)
{
	ssize_t	i;

	if (!argv)
		return ;
	s->f = true;
	s->status = 0;
	i = 1;
	if (!argv[1])
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		s->status = 1;
	}
	while (argv[i])
	{
		if (!check_env_vari(argv[i]))
			s->status = 1;
		unset_env(argv[i], env);
		i++;
	}
}
