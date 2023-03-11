/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 21:32:13 by keys              #+#    #+#             */
/*   Updated: 2023/03/11 19:48:00 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*newline(t_token *token, t_redirect type)
{
	t_line	*new;

	new = calloc(sizeof(t_line), 1);
	if (!new)
		_err_malloc();
	new->token = token;
	new->type = type;
	return (new);
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

void	addline_utils(t_line **line, t_token *token, t_redirect type)
{
	t_line	*new;

	new = NULL;
	new = newline(token, type);
	line_addback(line, new);
}
