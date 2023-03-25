/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 20:54:01 by keys              #+#    #+#             */
/*   Updated: 2023/03/25 17:20:09 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
