/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:31:08 by marai             #+#    #+#             */
/*   Updated: 2023/06/25 13:02:01 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	env_utils(char **argv, t_env *env, t_status *s)
{
	char	**envp;
	ssize_t	i;

	i = 0;
	s->f = true;
	if (!argv || !argv[0])
		return (true);
	else if (!argv[1])
	{
		envp = make_env_args(env);
		while (envp && envp[i] && env)
		{
			if (env->value)
			{
				ft_putendl_fd(envp[i], STDOUT_FILENO);
			}
			i++;
			env = env->next;
		}
		ft_split_free(envp);
		return (true);
	}
	return (false);
}

void	env_buildin(char *argv[], t_env *env, t_status *s)
{
	s->f = true;
	s->status = 0;
	if (argv[0] && argv[1])
	{
		s->status = 1;
		ft_putendl_fd("too many argument", 2);
		return ;
	}
	env_utils(argv, env, s);
}
