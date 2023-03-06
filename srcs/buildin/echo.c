/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:57:09 by keys              #+#    #+#             */
/*   Updated: 2023/03/06 09:50:29 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
// #include <limits.h>
// #include <unistd.h>

// void	ft_putstr_fd(char *s, int fd)
// {
// 	size_t	len;

// 	len = 0;
// 	if (!s)
// 		return ;
// 	len = strlen(s);
// 	if (len <= INT_MAX)
// 		write(fd, s, len);
// 	else
// 	{
// 		write(fd, s, INT_MAX);
// 		ft_putstr_fd(&s[INT_MAX], fd);
// 	}
// }

// void	ft_putendl_fd(char *s, int fd)
// {
// 	ft_putstr_fd(s, fd);
// 	write(fd, "\n", 1);
// }

// bool	is_operation_n(char *argv)
// {
// 	size_t	i;
// 	bool	flag;

// 	flag = 0;
// 	i = 0;
// 	if (argv[i] == '-')
// 		i++;
// 	else
// 		return (true);
// 	while (1)
// 	{
// 		if (flag == 1 && argv[i] == '\0')
// 			return (false);
// 		else if (argv[i] == 'n')
// 		{
// 			flag = 1;
// 			i++;
// 		}
// 		else
// 			break ;
// 	}
// 	return (true);
// }

// char	**operation_n(char **argv, bool *flag)
// {
// 	size_t	i;

// 	i = 0;
// 	while (1)
// 	{
// 		if (!argv[i] ||is_operation_n(argv[i]))
// 			break ;
// 		*flag = true;
// 		i++;
// 	}
// 	return (&argv[i]);
// }

// void	ft_echo(char **argv, int fd)
// {
// 	size_t	i;
// 	bool	flag;

// 	flag = 0;
// 	i = 0;
// 	argv = operation_n(argv, &flag);
// 	while (1)
// 	{
// 		if (!argv[i])
// 			break ;
// 		ft_putstr_fd(argv[i], fd);
// 		i++;
// 		if(argv[i])
// 			write(fd," ",1);
// 	}
// 	if (flag == false)
// 		write(fd, "\n", 1);
// }

// int	main(int argc,char **argv)
// {
// 	(void)argc;
// 	ft_echo(++argv, 1);
// }
// /*
// -n test
// -nnnnnnnn  test
// -n -n test
// -n-n test
// ----n test
// tewtt\ntest
// */
