/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:06:46 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/06 11:56:21 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	g_syntax_err = false;

bool	_err_syntax(char *mes)
{
	exit_status = 2;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", mes);
	return (true);
}

bool	err_syntax(char *op)
{
	if (strncmp(op, "||", 2) == 0)
		return (_err_syntax("||"));
	if (strncmp(op, "&&", 2) == 0)
		return (_err_syntax("&&"));
	if (strncmp(op, ";;", 2) == 0)
		return (_err_syntax(";;"));
	if (strncmp(op, "|&", 2) == 0)
		return (_err_syntax("|&"));
	if (strncmp(op, "&", 1) == 0)
		return (_err_syntax("&"));
	if (strncmp(op, "(", 1) == 0)
		return (_err_syntax("()"));
	if (strncmp(op, ")", 1) == 0)
		return (_err_syntax(")"));
	if (strncmp(op, ";", 1) == 0)
		return (_err_syntax(";"));
	return (false);
}

bool	syntax_check(t_token *token)
{
	while (1)
	{
		if (token->type == T_EOF)
			break ;
		if (token->type == OP)
		{
			if (err_syntax(token->word))
				return (true);
		}
		token = token->next;
	}
	return (false);
}

bool	token_error(t_token *token)
{
	if (token == NULL)
		return (true);
	if (syntax_check(token))
		return (true);
	return (false);
}
