/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahitoarai <masahitoarai@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:36 by keys              #+#    #+#             */
/*   Updated: 2023/06/07 16:00:08 by masahitoara      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAXLEN 260

char	*get_pwd(char *buf, size_t size, t_status *s)
{
	char	*p;

	p = getcwd(buf, size);
	if (!p)
	{
		s->status = errno;
		s->err_ms = strdup("Fatal Error: getcwd");
		if (!s->err_ms)
			_err_malloc();
	}
	return (p);
}

void	ft_pwd(t_status *s)
{
	char	buf[MAXLEN];
	char	*pwd;

	s->f = true;
	pwd = get_pwd(buf, sizeof(buf), s);
	if (pwd)
	{
		write(1, pwd, strlen(pwd));
		write(1, "\n", 1);
	}
}
