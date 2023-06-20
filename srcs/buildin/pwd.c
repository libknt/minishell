/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:36 by keys              #+#    #+#             */
/*   Updated: 2023/06/20 15:18:31 by ubuntu2204       ###   ########.fr       */
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
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
		free(pwd);
	}
}
