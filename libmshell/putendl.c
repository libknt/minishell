/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:44:19 by keys              #+#    #+#             */
/*   Updated: 2023/03/12 19:54:49 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmshell.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
