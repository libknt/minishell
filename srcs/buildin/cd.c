/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahitoarai <masahitoarai@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:56 by keys              #+#    #+#             */
/*   Updated: 2023/06/11 03:32:51masahitoara      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH_MAXLEN 4096

void	imple_pwd(t_env *head, t_status *s);

char	*get_home_dir(t_env *env)
{
	char	*homepath;

	while (env)
	{
		if (!strcmp(env->key, "HOME"))
		{
			homepath = strdup(env->value);
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
	if (!strcmp(argv, "~"))
	{
		memset(path, '\0', PATH_MAXLEN);
		ft_strlcpy(path, home, PATH_MAXLEN);
		return (path);
	}
	if (!strncmp(argv, "~/", 2))
	{
		memset(path, '\0', PATH_MAXLEN);
		ft_strlcpy(path, home, PATH_MAXLEN);
		i = 2;
	}
	if (!strncmp(argv, "./", 2))
		i = 2;
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	while (argv[i])
	{
		ft_strlcat(path, &argv[i], ft_strlen(path) + 2);
		i++;
	}
	return (path);
}

int	cd(char *argv[], t_env *env, t_status *s)
{
	char	path[PATH_MAXLEN];
	char	*home;
	int		status;

	s->f = true;
	home = get_home_dir(env);
	if (home == NULL)
	{
		dprintf(STDERR_FILENO, "HOME not set\n");
		return (-1);
	}
	if (!argv[1])
		status = chdir(home);
	else if (argv[1][0] == '/')
		status = chdir(argv[1]);
	else
	{
		memset(path, '\0', PATH_MAXLEN);
		getcwd(path, PATH_MAXLEN);
		make_abs_path(path, argv[1], home);
		status = chdir(path);
	}
	free(home);
	if (status < 0)
		dprintf(STDERR_FILENO, "bash: cd: too many arguments\n");
	else
		imple_pwd(env, s);
	return (0);
}

void	imple_pwd(t_env *head, t_status *s)
{
	char	*path;
	bool	isPWD;
	t_env	*env;

	env = head;
	isPWD = false;	
	while(env)
	{
		if(!strcmp("PWD", env->key))
		{
			if(env->value)
			{
				ft_env_addback(&head, make_env("OLDPWD", env->value));
				isPWD = true;
			}
		}
		env = env->next;
	}
	if(!isPWD)
		ft_env_addback(&head, make_env("OLDPWD", NULL));
	path = get_pwd(s);
	ft_env_addback(&head, make_env("PWD", path));
	free(path);
}