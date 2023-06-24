/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:36 by keys              #+#    #+#             */
/*   Updated: 2023/06/24 21:22:38 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAXLEN 260

char	*get_pwd(t_status *s)
{
	char	*p;
	char	buf[MAXLEN];

	ft_memset(buf, 0, MAXLEN);	
	p = getcwd(buf, sizeof(buf));
	if (!p)
	{
		s->status = errno;
		ft_putendl_fd("Fatal Error: getcwd", 2);
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
	}
	if (pwd)
		free(pwd);
}
