/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:57:09 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 19:13:32 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	is_operation_n(char *argv)
{
	size_t	i;
	bool	flag;

	flag = 0;
	i = 0;
	if (argv[i] == '-')
		i++;
	else
		return (true);
	while (1)
	{
		if (flag == 1 && argv[i] == '\0')
			return (false);
		else if (argv[i] == 'n')
		{
			flag = 1;
			i++;
		}
		else
			break ;
	}
	return (true);
}

char	**operation_n(char **argv, bool *flag)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (!argv[i] ||is_operation_n(argv[i]))
			break ;
		*flag = true;
		i++;
	}
	return (&argv[i]);
}

void	ft_echo(char **argv)
{
	size_t	i;
	bool	flag;

	flag = 0;
	i = 0;
	argv++;
	argv = operation_n(argv, &flag);
	while (1)
	{
		if (!argv[i])
			break ;
		ft_putstr_fd(argv[i], 1);
		i++;
		if(argv[i])
			write(1," ",1);
	}
	if (flag == false)
		write(1, "\n", 1);
}

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
