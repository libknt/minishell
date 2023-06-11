/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahitoarai <masahitoarai@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:44:10 by keys              #+#    #+#             */
/*   Updated: 2023/06/11 13:05:51 by masahitoara      ###   ########.fr       */
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
		printf("\n");
		ft_putstr_fd("\n", STDERR_FILENO);
		g_global.exit_status = 130;
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
		g_global.exit_status = 130;
	}
	else if (g_global.sig == SIGQUIT)
	{
		rl_done = 1;
	}
	g_global.sig = 0;
	return (0);
}

void	set_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = sig_handler;
	sig_int.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = sig_handler;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	reset_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = SIG_DFL;
	sig_int.sa_flags = 0;
	sigaction(SIGINT, &sig_int, NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_DFL;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT, &sig_quit, NULL);
}
