/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:36:46 by marai             #+#    #+#             */
/*   Updated: 2023/06/21 20:28:39 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *argv[], t_env **env, t_status *s)
{
	ssize_t	i;
	t_env	*env_node;

	if (!argv[1])
	{
		ft_putendl_fd("unset: not enough arguments\n", 2);
		s->status = 1;
		return ;
	}
	s->f = true;
	i = 1;
	while (argv[i])
	{
		env_node = *env;
		while (env_node)
		{
			if (!ft_strcmp(argv[i], env_node->key))
			{
				if(env_node->prev)
					(env_node->prev)->next = env_node->next;
				else
					*env = NULL;
				if (env_node->next)
					(env_node->next)->prev = env_node->prev;
				free(env_node);
				break ;
			}
			env_node = env_node->next;
		}
		i++;
	}
	s->status = 0;
}
