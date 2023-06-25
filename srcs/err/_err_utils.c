/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:02:45 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (!s)
		return ;
	len = ft_strlen(s);
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
