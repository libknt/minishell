/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:34:18 by marai             #+#    #+#             */
/*   Updated: 2023/03/25 17:23:55 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//use strcmp
#include "minishell.h"
extern t_global	g_global;

static void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (!s)
		return ;
	len = strlen(s);
	if (len <= INT_MAX)
		write(fd, s, len);
	else
	{
		write(fd, s, INT_MAX);
		ft_putstr_fd(&s[INT_MAX], fd);
	}
}

static void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	buildin_return(t_status *s)
{
	if (s->f == false)
		return (0);
	g_global.exit_status = s->status;
	if (s->status == 0)
		return (1);
	ft_putendl_fd(s->err_ms, 2);
	return (1);
}

int	buildin_simple(char *argv[], t_env **env, t_node *node)
{
	t_status	*s;

	s = new_status();
	if (!argv)
		return (0);
	if (!strcmp(argv[0], "cd"))
		cd(argv, *env, s);
	else if (!strcmp(argv[0], "export"))
		ft_export(argv, env, s);
	else if (!strcmp(argv[0], "env"))
		env_buildin(argv, *env, node, s);
	else if (!strcmp(argv[0], "unset"))
		unset(argv, env, s);
	else if (!strcmp(argv[0], "echo"))
		ft_echo(argv, s);
	else if (!strcmp(argv[0], "pwd"))
		ft_pwd(s);
	else if (!strcmp(argv[0], "exit"))
		ft_exit(argv, s);
	return (buildin_return(s));
}
