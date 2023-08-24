/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:44:10 by keys              #+#    #+#             */
/*   Updated: 2023/08/24 21:21:08 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	sig_handler(int sig)
{
	g_global.sig = sig;
}

int	exec_action(void)
{
	if (g_global.sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_global.exit_status = 1;
	}
	else if (g_global.sig == SIGQUIT)
	{
		ft_putstr_fd("Quit(core dump)\n", STDERR_FILENO);
		g_global.exit_status = 131;
	}
	g_global.sig = 0;
	return (0);
}

int	check_state(void)
{
	if (g_global.sig == 0)
		return (0);
	else if (g_global.sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		g_global.interrupt = true;
		g_global.exit_status = 1;
	}
	else if (g_global.sig == SIGQUIT)
	{
		rl_redisplay();
		g_global.interrupt = true;
	}
	g_global.sig = 0;
	return (0);
}
