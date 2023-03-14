/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marai <MasaDevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:44:10 by keys              #+#    #+#             */
/*   Updated: 2023/03/14 12:09:08 by Marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
extern t_global	global;

void	sig_handler(int sig)
{
	global.sig = sig;
}

int	exec_action(void)
{
	if (global.sig == SIGINT)
	{
		printf("\n");
		global.exit_status = 130;
	}
	else if(global.sig == SIGQUIT)
	{
		printf("\nQuit(core dumped)\n");
		global.exit_status = 131;
	}
	global.sig = 0;
	return (0);
}

int	check_state(void)
{
	if (global.sig == 0)
		return (0);
	else if (global.sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
		global.interrupt = true;
		global.exit_status = 130;
	}
	global.sig = 0;
	return (0);
}


void	set_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = sig_handler;
	sig_int.sa_flags = 0;
	sigaction(SIGINT,&sig_int,NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = sig_handler;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT,&sig_quit,NULL);
}

void	reset_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = SIG_DFL;
	sig_int.sa_flags = 0;
	sigaction(SIGINT,&sig_int,NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_DFL;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT,&sig_quit,NULL);
}
