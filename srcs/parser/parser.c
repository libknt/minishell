/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:24:57 by keys              #+#    #+#             */
/*   Updated: 2023/03/06 13:45:23 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_redirect(t_token *token)
{
	return ((strncmp(token->word, "<<", 2) == 0) || (strncmp(token->word, ">>",
				2) == 0) || (strncmp(token->word, "<", 1) == 0)
		|| (strncmp(token->word, ">", 1) == 0));
}

t_node	*newnode(t_token *token)
{
	t_node	*new;

	new = calloc(sizeof(t_node), 1);
	if (!new)
		_err("malloc");
	new->line = make_line(token);
	return (new);
}

void	node_addtree(t_node **node, t_node *new)
{
	t_node	*tmp;

	if (node)
	{
		if (*node)
		{
			tmp = *node;
			if (new->line->type == PIPE)
			{
				(*node) = new;
				new->left = tmp;
			}
			else
				tmp->right = new;
		}
		else
			*node = new;
	}
}

void	make_tree(t_node **node, t_token *token)
{
	t_node	*new;

	if (token->type == T_EOF)
		return ;
	else if (token->type == OP)
	{
		new = newnode(token);
		node_addtree(node, new);
		token = token->next;
		make_tree(node, token);
	}
	else
	{
		new = newnode(token);
		node_addtree(node, new);
		while (1)
		{
			if (token->type != WORD)
				break ;
			token = token->next;
		}
		make_tree(node, token);
	}
}

t_node	*parser(t_token *token, char *line)
{
	t_node	*tree;

	tree = NULL;
	make_tree(&tree, token);
	if (parse_err(tree))
	{
		tree_free(tree);
		token_free(&token);
		free(line);
		return (NULL);
	}
	return (tree);
}
