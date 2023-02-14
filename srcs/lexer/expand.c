/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyoda <kyoda@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 09:39:10 by kyoda             #+#    #+#             */
/*   Updated: 2023/02/14 10:19:19 by kyoda            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_quote(char *word)
{
	size_t	len;
	char	*new;

	len = strlen(word);
	new = malloc(sizeof(len - 1));
	if (!new)
		_err("malloc");
	new = ft_substr(word, 1, len - 2);
	free(word);
	return (new);
}

void	remake_token(t_token *token)
{
	if (token->type == TK_EOF)
		return ;
	else
	{
		if (token->type == WORD)
		{
			if (strncmp(token->word, "\"", 1) == 0 ||\
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