/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/03/05 22:07:32 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;
void	_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit_status = 1;
	exit(127);
}
/*

void	_err_syntax(char *mes)
{
	exit_status = 2;
	g_syntax_err = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", mes);
}

void	_err_syntax_p(char *mes)
{
	exit_status = 2;
	g_parse_err = true;
	dprintf(STDERR_FILENO, "1minishell: syntax error near %s\n", mes);
}

void	_err_parse_p(char *mes)
{
	exit_status = 2;
	g_parse_err = true;
	dprintf(STDERR_FILENO, "minishell: parse error near %s\n", mes);
}

*/
