/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masahitoarai <masahitoarai@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:36 by keys              #+#    #+#             */
/*   Updated: 2023/06/11 03:57:32 by masahitoara      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAXLEN 260

char	*get_pwd(t_status *s)
{
	char	*p;
	char	buf[MAXLEN];

	p = getcwd(buf, sizeof(buf));
	if (!p)
	{
		s->status = errno;
		s->err_ms = strdup("Fatal Error: getcwd");
		if (!s->err_ms)
			_err_malloc();
		return (NULL);
	}
	return (ft_strdup(p));
}

void	ft_pwd(t_status *s)
{
	char	*pwd;

	s->f = true;
	pwd = get_pwd(s);
	if (pwd)
	{
		write(1, pwd, strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
	}
}
