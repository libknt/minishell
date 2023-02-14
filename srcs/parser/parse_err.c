/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:21:12 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 16:26:36 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_parse_err = false;

void	_err_syntax_parse(char *mes)
{
	g_parse_err = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", mes);
}

void	syntax_parse(t_node *node)
{
	if (node->left)
		syntax_parse(node->left);
	if (node->t->type == WORD)
		return ;
	if (node->right == NULL)
	{
		_err_syntax_parse("syntax::parse");
	}
}

bool	parse_err(t_node *node)
{
	bool	re;

	syntax_parse(node);
	re = g_parse_err;
	return (re);
}
