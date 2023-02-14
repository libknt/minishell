/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:21:12 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 23:38:18 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_parse_err = false;

void	_err_syntax_p(char *mes)
{
	g_parse_err = true;
	dprintf(STDERR_FILENO, "1minishell: syntax error near %s\n", mes);
}

void	_err_parse_p(char *mes)
{
	g_parse_err = true;
	dprintf(STDERR_FILENO, "minishell: parse error near %s\n", mes);
}

void	check_syntax(t_node *node)
{
	t_line	*line;

	if (node->line->type == PIPE)
		_err_parse_p(node->line->token->word);
	else
	{
		line = node->line;
		while (1)
		{
			if ((line == NULL) || (line->type == T_EOF_R))
			{
				break ;
			}
			else
			{
				if (line->type == REDIRECT)
				{
					if ((!(line->next) || line->next->type != FILENAME))
					{
						_err_syntax_p(line->token->word);
						break ;
					}
					line = line->next;
				}
				else
				{
					line = line->next;
				}
			}
		}
	}
}

void	syntax_parse(t_node *node)
{
	if (!node->left && !node->right)
	{
		check_syntax(node);
		return ;
	}
	if (node->left == NULL)
	{
		_err_syntax_p(node->line->token->word);
		return ;
	}
	if (node->right == NULL)
	{
		_err_syntax_p(node->line->token->word);
		return ;
	}
	syntax_parse(node->left);
	syntax_parse(node->right);
	return ;
}

bool	parse_err(t_node *node)
{
	bool	re;

	syntax_parse(node);
	re = g_parse_err;
	return (re);
}
