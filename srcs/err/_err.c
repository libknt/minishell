/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 18:47:03 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit_status = 1;
	exit(127);
}

void	_err_malloc(const char *e) __attribute__((noreturn));
void _err_malloc(const char *e)
{

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
