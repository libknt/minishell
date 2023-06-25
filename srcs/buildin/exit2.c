/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 22:45:28 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:02:09 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_sign(char *str)
{
	if (str[0])
	{
		if ((str[0] == '-') || (str[0] == '+'))
		{
			if (str[1])
			{
				if ((str[1] == '-') || (str[1] == '+'))
				{
					ft_putendl_fd("exit", STDERR_FILENO);
					ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
					ft_putstr_fd(str, STDERR_FILENO);
					ft_putendl_fd(": numeric argument required", STDERR_FILENO);
					exit(255);
				}
			}
		}
	}
}
