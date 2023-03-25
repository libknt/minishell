/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:57:09 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 18:54:02 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operation_n(char *argv)
{
	size_t	i;
	bool	flag;

	flag = 0;
	i = 0;
	if (argv[i] == '-')
		i++;
	else
		return (true);
	while (1)
	{
		if (flag == 1 && argv[i] == '\0')
			return (false);
		else if (argv[i] == 'n')
		{
			flag = 1;
			i++;
		}
		else
			break ;
	}
	return (true);
}

char	**operation_n(char **argv, bool *flag)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (!argv[i] || is_operation_n(argv[i]))
			break ;
		*flag = true;
		i++;
	}
	return (&argv[i]);
}

void	ft_echo(char **argv, t_status *s)
{
	size_t	i;
	bool	flag;

	flag = 0;
	i = 0;
	argv++;
	s->f = true;
	argv = operation_n(argv, &flag);
	while (1)
	{
		if (!argv[i])
			break ;
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			write(1, " ", 1);
	}
	if (flag == false)
		write(1, "\n", 1);
}
