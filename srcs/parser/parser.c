/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:24:57 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 15:44:02 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*newnode(t_token *token)
{
	t_node	*new;

	new = calloc(sizeof(t_node), 1);
	if (!new)
		_err("malloc");
	new->t = token;
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
			if (new->t->type == OP)
			{
				(*node) = new;
				new->left = tmp;
			}
			else
			{
				tmp->right = new;
			}
		}
		else
		{
			*node = new;
		}
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

// void	add_trunk(t_node **tree, t_node *node, t_node *trunk)
// {
// 	t_node	*tmp;

// 	tmp = *tree;
// 	*tree = trunk;
// 	trunk->left = tmp;
// 	trunk->right = node;
// }

// void	make_trunk(t_node **tree, t_token *token)
// {
// 	t_node	*node;
// 	t_node	*tmp;

// 	node = NULL;
// 	if (tree)
// 	{
// 		while (token->type != T_EOF)
// 		{
// 			if ((token->type == OP && (strncmp(token->word, ";", 1) == 0)))
// 			{
// 				make_tree(&node, token);
// 				token = token->next;
// 			}
// 			else
// 			{
// 				make_tree(&node, token);
// 				while (1)
// 				{
// 					printf("LINE = %d\n", __LINE__);
// 					if (token->type == T_EOF)
// 						return ;
// 					if ((token->type == OP && (strncmp(token->word, ";",
// 									1) == 0)))
// 						break ;
// 					token = token->next;
// 				}
// 			}
// 			// make_tree(&node, token);
// 			// printf("\n\n\n");
// 			// print_tree(node);
// 			printf("LINE = %d\n", __LINE__);
// 			if (*tree)
// 			{
// 				tmp = newnode(token);
// 				add_trunk(tree, node, tmp);
// 			}
// 			else
// 				*tree = node;
// 		}
// 	}
// }

t_node	*parser(t_token *token)
{
	t_node	*tree;

	tree = NULL;
	make_tree(&tree, token);
	return (tree);
}
