/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:45:28 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 18:50:38 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

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
	if (i > 2)
	{
		g_global.exit_status = 1;
		write(2, "minishell: exit: too many arguments\n", 36);
	}
	else if (i == 1)
		exit(0);
	else
	{
		i = atol(argv[1]);
		i = i % 256;
		exit(i);
	}
}
