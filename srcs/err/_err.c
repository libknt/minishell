/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 19:16:00 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

static void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (!s)
		return ;
	len = strlen(s);
	if (len <= INT_MAX)
		write(fd, s, len);
	else
	{
		write(fd, s, INT_MAX);
		ft_putstr_fd(&s[INT_MAX], fd);
	}
}

static void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

void		_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	exit_status = 1;
	exit(127);
}

int			_err_malloc(void) __attribute__((noreturn));
int	_err_malloc(void)
{
	ft_putendl_fd("Fatal Error: memory not allocated.\n", STDERR_FILENO);
	exit_status = 1;
	exit(1);
}

/*lexer*/
bool	_err_syntax(char *m)
{
	ft_putstr_fd("minishell: syntax error near ", STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
	exit_status = 258;
	return (true);
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
