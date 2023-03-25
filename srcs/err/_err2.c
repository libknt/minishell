/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 18:38:18 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

bool	_err_syntax(char *m)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", \
	STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
	g_global.exit_status = 258;
	return (true);
}

void	_err_syntax_p(char *m, bool *r)
{
	*r = true;
	g_global.exit_status = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token ", \
	STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
}

void	_err_parse_p(char *m, bool *r)
{
	*r = true;
	g_global.exit_status = 258;
	ft_putstr_fd("minishell: parse error near unexpected token ", \
STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
}

void	*_err_nofile(t_node *node, char *m)
{
	g_global.exit_status = 1;
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	node->status = 1;
	return (NULL);
}

void	_err_cmd_not_found(char *m)
{
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putstr_fd(m, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	g_global.exit_status = 127;
}
