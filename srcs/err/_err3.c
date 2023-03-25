/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _err3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:24:55 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 18:36:25 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_global;

void	_err_minishell(char *m)
{
	g_global.exit_status = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(m, STDERR_FILENO);
}
