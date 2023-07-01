/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/07/01 12:59:45 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	*_err_no_such_file(char *m)
{
	g_global.exit_status = 127;
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (NULL);
}

void	*_err_period(char *m)
{
	g_global.exit_status = 2;
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": filename argument required", STDERR_FILENO);
	ft_putendl_fd("usage: . filename [arguments]", STDERR_FILENO);
	return (NULL);
}
