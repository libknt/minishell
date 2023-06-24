/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:31:08 by marai             #+#    #+#             */
/*   Updated: 2023/06/24 19:15:45 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_eql(char *str)
{
	ssize_t	i;

	if (!str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

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

	if (argv[0] && argv[1])
	{
		ft_putendl_fd("too many argument", 2);
		return ;
	}
	env_utils(argv, env, s);
}
