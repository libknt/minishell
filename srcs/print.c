/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:06:21 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 16:16:04 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_t(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (!(tmp))
			break ;
		printf("w =%s;\tt=%d;\t%p\t,p=%p\n", tmp->word, tmp->type, tmp,
				tmp->next);
		tmp = tmp->next;
	}
}

void	print_n(t_node *node)
{
	printf("%p\t%p\t%p\t", node, node->left, node->right);
	if (node->t->type == OP)
		printf("%s\n", node->t->word);
	else
	{
		while (1)
		{
			if (node->t->type != WORD)
				break ;
			printf("%s ", node->t->word);
			node->t = node->t->next;
		}
	}
}

void	print_node(t_node *node)
{
	if (node->left)
		print_node(node->left);
	if (node->right)
		print_node(node->right);
	print_n(node);
	printf("\n");
}

void	print_tree(t_node *node)
{
	// if ((node->t->type == OP) && (strncmp(node->t->word, ";", 1) == 0))
	// {
	// 	print_tree(node->left);
	// }
	print_node(node);
	// printf("%p\t%p\t%p\t", node, node->left, node->right);
	// printf("%s ", node->t->word);
	// printf("\n");
}
