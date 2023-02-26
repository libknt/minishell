/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:36 by keys              #+#    #+#             */
/*   Updated: 2023/02/26 16:10:02 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLEN 260

char	*get_pwd(char *buf, size_t size)
{
	char	*p;

	p = getcwd(buf, size);
	if (!p)
		exit(1);
	return (p);
}

void	ft_pwd(void)
{
	char	buf[MAXLEN];
	char	*pwd;

	pwd = get_pwd(buf, sizeof(buf));
	if (pwd == NULL)
		exit(1);
	printf("pwd %s\n", pwd);
}

// int	main(void)
// {
// 	ft_pwd();
// 	return (0);
// }
