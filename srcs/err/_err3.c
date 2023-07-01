/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/06/30 21:45:43 by ubuntu2204       ###   ########.fr       */
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