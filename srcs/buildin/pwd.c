/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:36 by keys              #+#    #+#             */
/*   Updated: 2023/03/10 00:34:04 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MAXLEN 260

char	*get_pwd(char *buf, size_t size)
{
	char	*p;

	p = getcwd(buf, size);
	if (!p)
		_err("getcwd");
	return (p);
}

void	ft_pwd(void)
{
	char	buf[MAXLEN];
	char	*pwd;

	pwd = get_pwd(buf, sizeof(buf));
	printf("pwd %s\n", pwd);
}
//https://learn.microsoft.com/ja-jp/windows/win32/fileio/maximum-file-path-limitation?tabs=registry
