/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:57:09 by keys              #+#    #+#             */
/*   Updated: 2023/02/28 20:19:38 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (!s)
		return ;
	len = strlen(s);
	if (len <= INT_MAX)
		write(fd, s, len);
	else
	{
		write(fd, s, INT_MAX);
		ft_putstr_fd(&s[INT_MAX], fd);
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void	ft_echo(char **argv, int fd)
{
	size_t	i;

	i = 1;
	while (1)
	{
		if (!argv[i])
			break ;
		ft_putendl_fd(argv[i], fd);
		i++;
	}
}
