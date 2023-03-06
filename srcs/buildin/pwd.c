/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:59:36 by keys              #+#    #+#             */
/*   Updated: 2023/03/06 09:50:11 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// // #include "minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// //https://learn.microsoft.com/ja-jp/windows/win32/fileio/maximum-file-path-limitation?tabs=registry
// #define MAXLEN 260

// char	*get_pwd(char *buf, size_t size)
// {
// 	char	*p;

// 	p = getcwd(buf, size);
// 	if (!p)
// 		_err("getcwd");
// 	return (p);
// }

// void	ft_pwd(void)
// {
// 	char	buf[MAXLEN];
// 	char	*pwd;

// 	pwd = get_pwd(buf, sizeof(buf));
// 	printf("pwd %s\n", pwd);
// }
