/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:30:45 by marai             #+#    #+#             */
/*   Updated: 2023/03/25 18:59:48 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_sort(char **envp)
{
	ssize_t	i;
	ssize_t	j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i;
		while (envp[j])
		{
			if (0 < strcmp(envp[i], envp[j]))
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

char	**free_envp(char **envp, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i <= len)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}

ssize_t	env_num(t_env *env)
{
	ssize_t	num;

	num = 0;
	while (env)
	{
		num++;
		env = env->next;
	}
	return (num);
}
