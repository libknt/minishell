/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:07:03 by keys              #+#    #+#             */
/*   Updated: 2023/02/26 20:22:44 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_node	**add_node(t_node *node)
{
	t_node	**tmp;

	if (node->left)
	{
		tmp = add_node(node->left);
		*tmp = node->right;
		return (&node->right->next);
	}
	return (&node->next);
}

void test(t_node *node)
{
	add_node(node);
	print_tree(node);
}
