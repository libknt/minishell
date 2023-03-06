/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:39:10 by kyoda             #+#    #+#             */
/*   Updated: 2023/02/26 17:29:05 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quote(char *word)
{
	size_t	len;
	char	*new;

	len = strlen(word);
	new = ft_substr(word, 1, len - 2);
	if (!new)
		_err("malloc");
	free(word);
	return (new);
}

void	remake_token(t_token *token)
{
	if (token->type == T_EOF)
		return ;
	else
	{
		if (token->type == WORD)
		{
			if (strncmp(token->word, "\"", 1) == 0 ||
				strncmp(token->word, "\'", 1) == 0)
				token->word = trim_quote(token->word);
		}
		remake_token(token->next);
	}
}

void	expand(t_token *token)
{
	remake_token(token);
}
