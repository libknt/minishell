/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:06:46 by kyoda             #+#    #+#             */
/*   Updated: 2023/02/26 17:20:50 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_syntax_err = false;

void	_err_syntax(char *mes)
{
	g_syntax_err = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", mes);
}

void	err_syntax(char *op)
{
	if (strncmp(op, "||", 2) == 0)
		_err_syntax("||");
	if (strncmp(op, "&&", 2) == 0)
		_err_syntax("&&");
	if (strncmp(op, ";;", 2) == 0)
		_err_syntax(";;");
	if (strncmp(op, "|&", 2) == 0)
		_err_syntax("|&");
	if (strncmp(op, "&", 1) == 0)
		_err_syntax("&");
	if (strncmp(op, "(", 1) == 0)
		_err_syntax("()");
	if (strncmp(op, ")", 1) == 0)
		_err_syntax(")");
	if (strncmp(op, ";", 1) == 0)
		_err_syntax(";");
}

void	syntax_check(t_token *token)
{
	if (token->type == T_EOF)
		return ;
	else
	{
		if (token->type == OP)
			err_syntax(token->word);
		syntax_check(token->next);
	}
}

bool	token_error(t_token *token)
{
	bool	re;

	g_syntax_err = false;
	syntax_check(token);
	re = g_syntax_err;
	return (re);
}
