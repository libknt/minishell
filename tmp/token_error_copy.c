/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error_copy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:06:46 by kyoda             #+#    #+#             */
/*   Updated: 2023/03/04 21:34:42 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// bool	g_syntax_err = false;

// void	_err_syntax(char *mes)
// {
// 	exit_status = 2;
// 	g_syntax_err = true;
// 	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", mes);
// }

// void	err_syntax(char *op)
// {
// 	if (strncmp(op, "||", 2) == 0)
// 		_err_syntax("||");
// 	if (strncmp(op, "&&", 2) == 0)
// 		_err_syntax("&&");
// 	if (strncmp(op, ";;", 2) == 0)
// 		_err_syntax(";;");
// 	if (strncmp(op, "|&", 2) == 0)
// 		_err_syntax("|&");
// 	if (strncmp(op, "&", 1) == 0)
// 		_err_syntax("&");
// 	if (strncmp(op, "(", 1) == 0)
// 		_err_syntax("()");
// 	if (strncmp(op, ")", 1) == 0)
// 		_err_syntax(")");
// 	if (strncmp(op, ";", 1) == 0)
// 		_err_syntax(";");
// }

// void	syntax_check(t_token *token)
// {
// 	if (token->type == T_EOF)
// 		return ;
// 	else
// 	{
// 		if (token->type == OP)
// 			err_syntax(token->word);
// 		syntax_check(token->next);
// 	}
// }

// bool	token_error(t_token *token)
// {
// 	// bool	re;

// 	// if (token == NULL)
// 	// 	return (true);
// 	// // re = false;
// 	// syntax_check(token);
// 	// re = g_syntax_err;
// 	// return (re);
// 	return false;
// }
