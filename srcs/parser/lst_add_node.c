/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marai <MasaDevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:07:03 by keys              #+#    #+#             */
/*   Updated: 2023/02/27 00:13:15 by Marai            ###   ########.fr       */
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
	//print_tree(node);
}
