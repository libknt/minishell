/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:44:10 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 00:46:54 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

extern int exit_status;
void	ctr_c(int sig)
{
	(void)sig;
	exit_status =130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signal(void)
{
	//if (signal(SIGINT, ctr_c) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	//{
	//	rl_clear_history();
	//	printf("SIGERR\n");
	//	exit(1);
	//}
	struct sigaction	sig_int;
	struct sigaction	sig_quit;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_handler = ctr_c;
	sig_int.sa_flags = 0;
	sigaction(SIGINT,&sig_int,NULL);
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_handler = SIG_IGN;
	sig_int.sa_flags = 0;
	sigaction(SIGQUIT,&sig_quit,NULL);

}
