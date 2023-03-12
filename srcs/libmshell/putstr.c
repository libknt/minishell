/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:43:58 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:55:15 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

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
