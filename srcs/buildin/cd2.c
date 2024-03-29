/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:26:55 by marai             #+#    #+#             */
/*   Updated: 2023/06/25 13:01:56 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_err_check(char *path, int status)
{
	if (status < 0)
	{
		if (!access(path, F_OK) && (access(path, R_OK) == -1 || \
			access(path, X_OK) == -1))
			ft_putendl_fd("minishell: cd: permission denied", STDERR_FILENO);
		else
			ft_putendl_fd(" No such file or directory", STDERR_FILENO);
	}
	return ;
}

char	*get_home_dir(t_env *env)
{
	char	*homepath;

	while (env)
	{
		if (!ft_strcmp(env->key, "HOME"))
		{
			homepath = ft_strdup(env->value);
			if (!homepath)
				_err_malloc();
			return (homepath);
		}
		env = env->next;
	}
	return (NULL);
}

bool	is_home_set(char *home)
{
	if (!home)
	{
		ft_putendl_fd("HOME not set", STDERR_FILENO);
		return (false);
	}
	return (true);
}

char	*make_home_path(char *path, char *home)
{
	if (!is_home_set(home))
		return (NULL);
	ft_memset(path, '\0', PATH_MAXLEN);
	ft_strlcpy(path, home, PATH_MAXLEN);
	return (path);
}

void	imple_pwd(t_env **head, t_status *s)
{
	char	*path;
	bool	is_pwd;
	t_env	*env;

	env = *head;
	is_pwd = false;
	while (env)
	{
		if (!ft_strcmp("PWD", env->key))
		{
			if (env->value)
			{
				ft_env_addback(head, make_env("OLDPWD", env->value));
				is_pwd = true;
			}
		}
		env = env->next;
	}
	if (!is_pwd && head)
		ft_env_addback(head, make_env("OLDPWD", NULL));
	path = get_pwd(s);
	if (head && path)
		ft_env_addback(head, make_env("PWD", path));
	if (path)
		free(path);
}
