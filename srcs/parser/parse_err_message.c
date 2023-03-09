/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:22:18 by keys              #+#    #+#             */
/*   Updated: 2023/03/05 21:23:21 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;
void	_err_syntax_p(char *mes, bool *r)
{
	exit_status = 2;
	*r = true;
	dprintf(STDERR_FILENO, "1minishell: syntax error near %s\n", mes);
}

void	_err_parse_p(char *mes, bool *r)
{
	exit_status = 2;
	*r = true;
	dprintf(STDERR_FILENO, "minishell: parse error near %s\n", mes);
}
