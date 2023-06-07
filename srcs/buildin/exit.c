/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:45:28 by keys              #+#    #+#             */
/*   Updated: 2023/06/07 22:56:50 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

static int	ft_isal(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	return (0);
}

void check_str(char *str)
{
	size_t i; 	

	i = 0;
	if(*str == '\0')
		exit(2);
	while(1)
	{
		if(str[i] == '\0')
			return ;
		else
		{
			if(ft_isal(str[i]) == 1)
				exit(2);
		}
		i++;
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
	if (i > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 35);
		s->status = 1;
		return ;
	}
	else if (i == 1)
		exit(0);
	else
	{
		if(argv[1][0] == '\0')
		{
			write(2, "minishell: exit: : numeric argument required\n", 44);
			exit(2);
		}
		else
		{
			check_str(argv[1]);
			i = atol(argv[1]);
			i = i % 256;
			exit(i);
		}
	}
}
