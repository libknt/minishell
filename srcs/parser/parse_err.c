/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:21:12 by keys              #+#    #+#             */
/*   Updated: 2023/03/05 21:22:43 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_line(t_line *line, bool *r)
{
	while (1)
	{
		if ((line == NULL) || (line->type == T_EOF_R))
			break ;
		else
		{
			if (line->type == REDIRECT)
			{
				if ((!(line->next) || line->next->type != FILENAME))
				{
					_err_syntax_p(line->token->word, r);
					break ;
				}
				line = line->next;
			}
			else
				line = line->next;
		}
	}
}

void	check_syntax(t_node *node, bool *r)
{
	t_line	*line;

	if (*r == true)
		return ;
	if (node->line->type == PIPE)
	{
		_err_parse_p(node->line->token->word, r);
	}
	else
	{
		line = node->line;
		check_line(line, r);
	}
}

void	syntax_parse(t_node *node, bool *r)
{
	if (*r == true)
		return ;
	if (!node->left && !node->right)
	{
		check_syntax(node, r);
		return ;
	}
	if (node->left == NULL)
	{
		_err_syntax_p(node->line->token->word, r);
		return ;
	}
	if (node->right == NULL)
	{
		_err_syntax_p(node->line->token->word, r);
		return ;
	}
	syntax_parse(node->left, r);
	syntax_parse(node->right, r);
}

bool	parse_err(t_node *node)
{
	bool	r;

	r = false;
	syntax_parse(node, &r);
	return (r);
}
