/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:40:13 by keys              #+#    #+#             */
/*   Updated: 2023/03/04 23:12:26 by keys             ###   ########.fr       */
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
	*token = NULL;
	token = NULL;
}
