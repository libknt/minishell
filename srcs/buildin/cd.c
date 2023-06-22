/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:56 by keys              #+#    #+#             */
/*   Updated: 2023/06/22 13:38:47 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH_MAXLEN 4096

void	imple_pwd(t_env **head, t_status *s);

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

char	*make_abs_path(char *path, char *argv, char *home)
{
	ssize_t	i;

	i = 0;
	if (!ft_strcmp(argv, "~"))
	{
		if (!home)
		{
			ft_putendl_fd("HOME not set", STDERR_FILENO);
			return (NULL);
		}
		ft_memset(path, '\0', PATH_MAXLEN);
		ft_strlcpy(path, home, PATH_MAXLEN);
		return (path);
	}
	if (!ft_strncmp(argv, "~/", 2))
	{
		if (!home)
		{
			ft_putendl_fd("HOME not set", STDERR_FILENO);
			return (NULL);
		}
		ft_memset(path, '\0', PATH_MAXLEN);
		ft_strlcpy(path, home, PATH_MAXLEN);
		i = 2;
	}
	if (!ft_strncmp(argv, "./", 2))
		i = 2;
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	while (argv[i])
	{
		ft_strlcat(path, &argv[i], ft_strlen(path) + 2);
		i++;
	}
	return (path);
}

int	move_to_abs_path(char *path)
{
	int		status;

	status =  chdir(path);
	if (status < 0)
		ft_putendl_fd(" No such file or directory", STDERR_FILENO);
	
	return (status);
}

int	move_to_home_or_rel_path(char *path[], t_env *env, t_status *s)
{
	char	home_path[PATH_MAXLEN];
	char	*home;
	int		status;

	home = get_home_dir(env);
	if (!path[1])
	{
		if (!home)
		{
			ft_putendl_fd("HOME not set", STDERR_FILENO);
			s->status = 1;
			return (-1);
		}
		status = chdir(home);
	}
	else
	{
		ft_memset(home_path, '\0', PATH_MAXLEN);
		getcwd(home_path, PATH_MAXLEN);
		make_abs_path(home_path, path[1], home);
		status = chdir(home_path);
	}
	if (home)
		free(home);
	if (status < 0)
		ft_putendl_fd(" No such file or directory", STDERR_FILENO);
	
	return status;
}

void	handle_cd_status(int status, t_env **env, t_status *s)
{
	if (status < 0)
		s->status = 1;
	else
		imple_pwd(env, s);
}

int	cd(char *argv[], t_env **env, t_status *s)
{
	int		status;

	s->f = true;
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		status = -1;
	}
	else if (argv[1] && argv[1][0] == '/')
		status = move_to_abs_path(argv[1]);
	else
		status = move_to_home_or_rel_path(argv, *env, s);
	handle_cd_status(status, env, s);
	return (0);
}


// int	cd(char *argv[], t_env *env, t_status *s)
// {
// 	char	path[PATH_MAXLEN];
// 	char	*home;
// 	int		status;

// 	s->f = true;
// 	if (argv[1][0] == '/')
// 		status = chdir(argv[1]);
// 	else
// 	{
// 		home = get_home_dir(env);
// 		if (home == NULL)
// 		{
// 			ft_putendl_fd("HOME not set", STDERR_FILENO);
// 			s->status = 1;
// 			return (-1);
// 		}
// 		if (!argv[1])
// 			status = chdir(home);
// 		else
// 		{
// 			ft_memset(path, '\0', PATH_MAXLEN);
// 			getcwd(path, PATH_MAXLEN);
// 			make_abs_path(path, argv[1], home);
// 			status = chdir(path);
// 			free(home);
// 		}
// 	}
// 	if (status < 0)
// 	{
// 		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
// 	}
// 	else
// 		imple_pwd(env, s);
// 	return (0);
// }

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
	if (!is_pwd)
		ft_env_addback(head, make_env("OLDPWD", NULL));
	path = get_pwd(s);
	ft_env_addback(head, make_env("PWD", path));
	free(path);
}
