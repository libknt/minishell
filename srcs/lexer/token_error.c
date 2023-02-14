/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:06:46 by kyoda             #+#    #+#             */
/*   Updated: 2023/02/14 10:50:11 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"'

// void	err_syntax(char *op)
// {
// 	if (strncmp(op, "||", 2) == 0)
//         _err();
//         strncmp(op, "&&", 2) == 0 ||
// 		strncmp(op, ";;", 2) == 0 || 
//         strncmp(op, "|&", 2) == 0 ||
// 		strncmp(op, "&", 1) == 0 || 
//         strncmp(op, ";", 1) == 0 ||
// 		strncmp(op, "(", 1) == 0 || 
//         strncmp(op, ")", 1) == 0 ||
// 		return (TK_OP);
// 	return (WORD);
// }

// void	syntax_check(t_token *token)
// {
// 	if (token->type == TK_EOF)
// 		return ;
// 	else
// 	{
// 		if (token->type == TK_OP)
// 			err_syntax(token->word);
// 		syntax_check(token->next);
// 	}
// }

// void	token_error(t_token *token)
// {
// 	syntax_check(token);
// }