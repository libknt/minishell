/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:56 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:01:54 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_abs_path(char *path, char *argv, char *home)
{
	size_t	i;

	i = 0;
	if (!ft_strcmp(argv, "~"))
		return (make_home_path(path, home));
	if (!ft_strncmp(argv, "~/", 2))
	{
		if (!is_home_set(home))
			return (NULL);
		ft_memset(path, '\0', PATH_MAXLEN);
		ft_strlcpy(path, home, PATH_MAXLEN);
		i = 2;
	}
	if (!ft_strncmp(argv, "./", 2))
		i = 2;
	ft_strlcat(path, "/", ft_strlen(path) + 2);
	ft_strlcat(path, &argv[i], PATH_MAXLEN);
	return (path);
}

static int	move_to_abs_path(char *path)
{
	int		status;

	status = chdir(path);
	cd_err_check(path, status);
	return (status);
}

int	move_to_home_or_rel_path(char *path[], t_env *env)
{
	char	home_path[PATH_MAXLEN];
	char	*home;
	int		status;

	home = get_home_dir(env);
	if (!path[1])
	{
		if (!is_home_set(home))
			return (-1);
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
	cd_err_check(home_path, status);
	return (status);
}

static void	handle_cd_status(int status, t_env **env, t_status *s)
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
	else if (argv[1] && PATH_MAXLEN - 1 < ft_strlen(argv[1]))
	{
		ft_putstr_fd("minishell: cd: no such file or directory:", \
			STDERR_FILENO);
		ft_putendl_fd(argv[1], STDERR_FILENO);
		status = -1;
	}
	else if (argv[1] && argv[1][0] == '/')
		status = move_to_abs_path(argv[1]);
	else
		status = move_to_home_or_rel_path(argv, *env);
	handle_cd_status(status, env, s);
	return (0);
}
