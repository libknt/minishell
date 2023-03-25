/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:06:21 by keys              #+#    #+#             */
/*   Updated: 2023/02/27 16:18:36 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/////

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
	t_line	*tmp;

	printf("%p\t%p\t%p\t", node, node->left, node->right);
	if (node->line->type == PIPE)
		printf("%d  %s\n", node->line->type, node->line->token->word);
	else
	{
		tmp = node->line;
		while (1)
		{
			if (tmp->type == T_EOF_R)
				break ;
			printf("%d %s ", tmp->type, tmp->token->word);
			tmp = tmp->next;
			// if (node->t->type != WORD)
			// 	break ;
			// printf("%s ", node->t->word);
			// node->t = node->t->next;
		}
		printf("ptr %p",node->next);
		// print_n(node->next);
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
	print_node(node);
}

void	print_line(t_line *line)
{
	if (line)
	{
		while (1)
		{
			if (line == NULL || line->type == T_EOF_R)
			{
				printf("EOF");
				break ;
			}
			printf("%d:%s ",line->type, line->token->word);
			line = line->next;
		}
		printf("\n\n");
	}
}

void	print_split(char **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		printf("sp = %s\n", t[i]);
		i++;
	}
}
