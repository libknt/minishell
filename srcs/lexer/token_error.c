/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu2204 <ubuntu2204@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:06:46 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/20 15:29:06 by ubuntu2204       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	err_syntax(char *op)
{
	if (ft_strncmp(op, "||", 2) == 0)
		return (_err_syntax("||"));
	if (ft_strncmp(op, "&&", 2) == 0)
		return (_err_syntax("&&"));
	if (ft_strncmp(op, ";;", 2) == 0)
		return (_err_syntax(";;"));
	if (ft_strncmp(op, "|&", 2) == 0)
		return (_err_syntax("|&"));
	if (ft_strncmp(op, "&", 1) == 0)
		return (_err_syntax("&"));
	if (ft_strncmp(op, "(", 1) == 0)
		return (_err_syntax("()"));
	if (ft_strncmp(op, ")", 1) == 0)
		return (_err_syntax(")"));
	if (ft_strncmp(op, ";", 1) == 0)
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
	if (token->type == T_EOF)
		return (true);
	if (syntax_check(token))
		return (true);
	return (false);
}
