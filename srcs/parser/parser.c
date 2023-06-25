/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:24:57 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 13:04:04 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_redirect(t_token *token)
{
	if (token->type == EX_WORD)
	{
		token->type = WORD;
		return (false);
	}
	return ((ft_strncmp(token->word, "<<", 2) == 0) || (ft_strncmp(token->word,
				">>", 2) == 0) || (ft_strncmp(token->word, "<", 1) == 0)
		|| (ft_strncmp(token->word, ">", 1) == 0));
}

static t_node	*newnode(t_token *token)
{
	t_node	*new;

	new = ft_calloc(sizeof(t_node), 1);
	if (!new)
		_err_malloc();
	new->line = make_line(token);
	return (new);
}

static void	node_addtree(t_node **node, t_node *new)
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

static void	make_tree(t_node **node, t_token *token)
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
