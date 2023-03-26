/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:34:18 by marai             #+#    #+#             */
/*   Updated: 2023/03/26 16:34:59 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

t_status	*new_status(void)
{
	t_status	*new;

	new = calloc(1, sizeof(t_status));
	if (!new)
		_err_malloc();
	return (new);
}

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
	else if (!strcmp(str, "echo"))
		return (true);
	else if (!strcmp(str, "pwd"))
		return (true);
	else if (!strcmp(str, "exit"))
		return (true);
	return (false);
}

int	buildin_exit(t_status *s)
{
	if (s->f == false)
		return (0);
	else
	{
		g_global.exit_status = s->status;
		if (s->status == 0)
			exit(0);
		ft_putendl_fd(s->err_ms, 2);
		exit(s->status);
	}
	return (1);
}

int	buildin(char *argv[], t_env **env, t_node *node)
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
	return (buildin_exit(s));
}
