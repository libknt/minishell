/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <masadevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:34:18 by marai             #+#    #+#             */
/*   Updated: 2023/03/10 00:34:21 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_buildin(char *str)
{
	if (!str)
		return (false);
	else if (!strcmp(str, "cd"))
		return (true);
	else if (!strcmp(str, "export"))
		return (true);
	else if (!strcmp(str, "env"))
		return (true);
	else if (!strcmp(str, "unset"))
		return (true);
	return (false);
}

int	buildin(char *argv[], t_env **env)
{
	if (!argv)
		return (0);
	if (!strcmp(argv[0], "cd"))
	{
		cd(argv, *env);
		return (1);
	}
	else if (!strcmp(argv[0], "export"))
	{
		ft_export(argv, env);
		return (1);
	}
	else if (!strcmp(argv[0], "env"))
	{
		env_buildin(argv, *env);
		return (1);
	}
	else if (!strcmp(argv[0], "unset"))
	{
		unset(argv, env);
		return (1);
	}
	return (0);
}
