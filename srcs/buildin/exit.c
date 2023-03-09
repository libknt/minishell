/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:45:28 by keys              #+#    #+#             */
/*   Updated: 2023/03/10 00:35:19 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_exit(char **argv)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (argv[i])
			i++;
		else
			break ;
	}
	if (i > 2)
	{
		// exit_status = 1;
		write(2, "minishell: exit: too many arguments\n", 36);
	}
	else if (i == 1)
		exit(0);
	else
	{
		i = atol(argv[1]);
		while (1)
		{
			if (i > 255)
				i -= 256;
			else
				break ;
		}
		exit(i);
	}
}
