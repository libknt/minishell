/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/03/15 11:36:33 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	global;

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

void			_err(const char *e) __attribute__((noreturn));
void	_err(const char *e)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", e);
	global.exit_status = 1;
	exit(127);
}

int				_err_malloc(void) __attribute__((noreturn));
int	_err_malloc(void)
{
	ft_putendl_fd("Fatal Error: memory not allocated.\n", STDERR_FILENO);
	global.exit_status = 1;
	exit(1);
}

int				_err_fork(void) __attribute__((noreturn));
int	_err_fork(void)
{
	ft_putendl_fd("Fatal Error: fork.\n", STDERR_FILENO);
	global.exit_status = 1;
	exit(1);
}

int				_err_wait(int status) __attribute__((noreturn));
int	_err_wait(int status)
{
	ft_putendl_fd("wait error\n", STDERR_FILENO);
	global.exit_status = status;
	exit(status);
}
/*lexer*/
bool	_err_syntax(char *m)
{
	ft_putstr_fd("minishell: syntax error near unexpected token ",
					STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
	global.exit_status = 258;
	return (true);
}
/*parser*/
void	_err_syntax_p(char *m, bool *r)
{
	*r = true;
	global.exit_status = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token ",
					STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
}

void	_err_parse_p(char *m, bool *r)
{
	*r = true;
	global.exit_status = 258;
	ft_putstr_fd("minishell: parse error near unexpected token ",
					STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
}

void	*_err_nofile(t_node *node, char *m)
{
	global.exit_status = 1;
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
	global.exit_status = 127;
}

void	_err_minishell(char *m)
{
	global.exit_status = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
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
