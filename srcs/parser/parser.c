/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:24:57 by keys              #+#    #+#             */
/*   Updated: 2023/02/14 18:20:06 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*newline(t_token *token, t_redirect type)
{
	t_line	*new;

	new = calloc(sizeof(t_line), 1);
	if (!new)
		_err("malloc");
	new->token = token;
	new->type = type;
	return (new);
}
bool	find_redirect(t_token *token)
{
	return ((strncmp(token->word, "<<", 2) == 0) ||
			(strncmp(token->word, ">>", 2) == 0) ||
			(strncmp(token->word, "<", 1) == 0) ||
			(strncmp(token->word, ">", 1) == 0));
}

t_line	*line_last(t_line *token)
{
	t_line	*tmp;

	tmp = token;
	while (tmp)
	{
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	line_addback(t_line **head, t_line *new)
{
	t_line	*tmp;

	if (head)
	{
		if (*head)
		{
			tmp = line_last(*head);
			tmp->next = new;
		}
		else
			*head = new;
	}
}

t_line	*make_line(t_token *token)
{
	int		type;
	t_line	*line;
	t_line	*new;

	line = NULL;
	type = 0;
	if (token->type == OP)
		return (newline(token, PIPE));
	else
	{
		while (1)
		{
			if (token->type == T_EOF || token->type == OP)
				break ;
			if (find_redirect(token))
			{
				type = 1;
				new = newline(token, REDIRECT);
			}
			else if (type == 1)
			{
				type = 0;
				new = newline(token, FILENAME);
			}
			else
			{
				new = newline(token, CMDLINE);
			}
			line_addback(&line, new);
			token = token->next;
		}
	}
	new = newline(NULL, T_EOF_R);
	line_addback(&line, new);
	return (line);
}

t_node	*newnode(t_token *token)
{
	t_node	*new;

	(void)token;
	new = calloc(sizeof(t_node), 1);
	if (!new)
		_err("malloc");
	new->line = make_line(token);
	// new->line = NULL;
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
			// if (new->t->type == OP)
			if (new->line->type == PIPE)
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

t_node	*parser(t_token *token)
{
	t_node	*tree;

	tree = NULL;
	make_tree(&tree, token);
	return (tree);
}
