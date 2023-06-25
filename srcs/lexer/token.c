/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:24:17 by keys              #+#    #+#             */
/*   Updated: 2023/06/25 10:49:32 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*token_last(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (!(tmp->next))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	token_addback(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (head)
	{
		if (*head)
		{
			tmp = token_last(*head);
			tmp->next = new;
		}
		else
			*head = new;
	}
}

t_token	*new_token(char *str, t_token_type type)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		_err("calloc");
	new->ex_heredoc_flag = ft_calloc(sizeof(bool), 1);
	if (!new->ex_heredoc_flag)
		_err_malloc();
	new->type = type;
	new->word = str;
	return (new);
}
