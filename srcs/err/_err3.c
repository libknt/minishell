/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:02:53 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	_err_minishell(char *m)
{
	g_global.exit_status = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
}

void	_err_is_directory(char *m)
{
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": Is a directory", STDERR_FILENO);
	g_global.exit_status = 126;
}

void	_err_permission(char *m)
{
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": Permission denied", STDERR_FILENO);
	g_global.exit_status = 126;
}

void	_err_heredoc(char *m)
{
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": warning: wanted `EOF'", STDERR_FILENO);
}
