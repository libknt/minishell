/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:36:46 by marai             #+#    #+#             */
/*   Updated: 2023/06/28 14:18:03 by marai            ###   ########.fr       */
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

static bool	is_key_valid(char *str)
{
	ssize_t	i;

	i = 0;
	if (!str)
		return (false);
	if (!is_identifier(str))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": invalid parameter name", STDERR_FILENO);
		return (false);
	}
	return (true);
}

void	unset(char *argv[], t_env **env, t_status *s)
{
	ssize_t	i;

	if (!argv)
		return ;
	s->f = true;
	s->status = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_key_valid(argv[i]))
			s->status = 1;
		unset_env(argv[i], env);
		i++;
	}
}
