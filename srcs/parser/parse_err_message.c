/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:22:18 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 14:50:40 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
