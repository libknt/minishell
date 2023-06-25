/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:27:16 by kyoda             #+#    #+#             */
/*   Updated: 2023/06/25 13:03:22 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	line_free(t_line *line)
{
	t_line	*tmp;

	while (1)
	{
		if (line == NULL)
			break ;
		tmp = line->next;
		free(line);
		line = tmp;
	}
}

void	tree_free(t_node *tree)
{
	if (tree->left)
		tree_free(tree->left);
	if (tree->right)
		tree_free(tree->right);
	if (tree)
	{
		line_free(tree->line);
		free(tree);
	}
}
