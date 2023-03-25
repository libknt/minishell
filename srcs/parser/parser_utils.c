/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:54:01 by keys              #+#    #+#             */
/*   Updated: 2023/03/15 11:28:51 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_node	**add_node(t_node *node)
// {
// 	t_node	**tmp;

// 	if (node->left)
// 	{
// 		tmp = add_node(node->left);
// 		*tmp = node->right;
// 		return (&node->right->next);
// 	}
// 	return (&node->next);
// }

// t_node	**add_node(t_node **node)
// {
// 	t_node **tmp;

// 	if ((*node)->left)
// 	{
// 		tmp = add_node(&(*node)->left);
// 		(*tmp)->next = (*node)->right;
// 		(*node)->right->prev = *tmp;
// 		return (&(*node)->right);
// 	}
// 	return (node);
// }

t_node	**add_node(t_node *node)
{
	t_node	**tmp;
	t_node	**p;

	p = &node;
	if (node->left)
	{
		tmp = add_node(node->left);
		(*tmp)->next = node->right;
		node->right->prev = *tmp;
		return (&node->right);
	}
	return (p);
}
