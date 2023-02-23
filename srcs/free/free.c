/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:27:16 by kyoda             #+#    #+#             */
/*   Updated: 2023/02/21 14:45:22 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_free(t_token **token)
{
	t_token	*tmp;

	if (token)
	{
		while (1)
		{
			if (!(*token))
				break ;
			tmp = (*token)->next;
			free((*token)->word);
			(*token)->word = NULL;
			free(*token);
			(*token) = tmp;
		}
	}
}
void	line_free(t_line *line)
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
