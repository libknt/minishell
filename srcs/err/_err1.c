/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 18:45:18 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	g_global.exit_status = 1;
	exit(127);
}

int	_err_malloc(void)
{
	ft_putendl_fd("Fatal Error: memory not allocated.\n", STDERR_FILENO);
	g_global.exit_status = 1;
	exit(1);
}

int	_err_fork(void)
{
	ft_putendl_fd("Fatal Error: fork.\n", STDERR_FILENO);
	g_global.exit_status = 1;
	exit(1);
}

int	_err_wait(int status)
{
	ft_putendl_fd("wait error\n", STDERR_FILENO);
	g_global.exit_status = status;
	exit(status);
}
