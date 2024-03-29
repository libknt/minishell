/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:45:28 by keys              #+#    #+#             */
/*   Updated: 2023/07/01 17:18:18 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static void	check_str(char *str)
{
	size_t	i;

	i = 0;
	if (*str == '\0')
		exit(2);
	check_sign(str);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (1)
	{
		if (str[i] == '\0')
			return ;
		else
		{
			if (ft_isdigit(str[i]) != 1)
			{
				ft_putendl_fd("exit", STDERR_FILENO);
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(str, STDERR_FILENO);
				ft_putendl_fd(": numeric argument required", STDERR_FILENO);
				exit(255);
			}
		}
		i++;
	}
}

static void	handle_long_max_min(char **argv)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if ((ft_strcmp(argv[1], "9223372036854775807") != 0) && (ft_strcmp(argv[1],
				"-9223372036854775808") != 0))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	exit(255);
}

static void	handle_exit_with_arg(char **argv)
{
	size_t	i;

	if (argv[1][0] == '\0')
	{
		write(2, "minishell: exit: : numeric argument required\n", 44);
		exit(255);
	}
	else if (argv[1] && ((ft_atol(argv[1]) == LONG_MAX)
			|| (ft_atol(argv[1]) == LONG_MIN)))
		handle_long_max_min(argv);
	else
	{
		check_str(argv[1]);
		i = ft_atol(argv[1]);
		i %= 256;
		exit(i);
	}
}

static void	exe_exit(size_t i, char **argv, t_status *s)
{
	if (i == 2)
		handle_exit_with_arg(argv);
	else if (i > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		s->status = 1;
		return ;
	}
	else
	{
		i = g_global.exit_status;
		i = i % 256;
		exit(i);
	}
}

void	ft_exit(char **argv, t_status *s)
{
	size_t	i;

	i = 0;
	s->f = true;
	while (1)
	{
		if (argv[i])
			i++;
		else
			break ;
	}
	exe_exit(i, argv, s);
}
