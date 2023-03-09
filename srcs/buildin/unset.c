/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:36:46 by marai             #+#    #+#             */
/*   Updated: 2023/03/09 16:03:42 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	unset(char *argv[], t_env **env)
{
	ssize_t	i;
	t_env	*env_node;
	
	if(!argv)
		return ;
	i = 1;
	while(argv[i])
	{
		env_node = *env;
		while (env_node)
		{
			if(!strcmp(argv[i], env_node->key))
			{
				env_node->prev->next = env_node->next;
				env_node->next->prev = env_node->prev;
				free(env_node);
			}
			env_node = env_node->next;
		}
		i++;
	}
}