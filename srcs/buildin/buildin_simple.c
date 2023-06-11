/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahitoarai <masahitoarai@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:34:18 by marai             #+#    #+#             */
/*   Updated: 2023/06/11 03:57:22 by masahitoara      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

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

void	exec_buildin(char **argv, t_env **env, t_node *node, t_status *s)
{
	/*
	if (!isatty(1))
	{
		write(STDERR_FILENO,argv[0],strlen(argv[0]));
		write(STDERR_FILENO, ": write error: Bad file descriptor\n", 35);
		s->f = true;
		return ;
	}
	*/
	if (s->buildin_type == 1)
		cd(argv, *env, s);
	if (s->buildin_type == 2)
		ft_export(argv, env, s);
	if (s->buildin_type == 3)
		env_buildin(argv, *env, node, s);
	if (s->buildin_type == 4)
		unset(argv, env, s);
	if (s->buildin_type == 5)
		ft_echo(argv, s);
	if (s->buildin_type == 6)
		ft_pwd(s);
	if (s->buildin_type == 7)
		ft_exit(argv, s);
}

int	buildin_simple(char *argv[], t_env **env, t_node *node)
{
	t_status	*s;

	s = new_status();
	if (!argv)
		return (0);
	if (!strcmp(argv[0], "cd"))
		s->buildin_type = 1;
	else if (!strcmp(argv[0], "export"))
		s->buildin_type = 2;
	else if (!strcmp(argv[0], "env"))
		s->buildin_type = 3;
	else if (!strcmp(argv[0], "unset"))
		s->buildin_type = 4;
	else if (!strcmp(argv[0], "echo"))
		s->buildin_type = 5;
	else if (!strcmp(argv[0], "pwd"))
		s->buildin_type = 6;
	else if (!strcmp(argv[0], "exit"))
		s->buildin_type = 7;
	if (s->buildin_type)
		exec_buildin(argv, env, node, s);
	return (buildin_return(s));
}
