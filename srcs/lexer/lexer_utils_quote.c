/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:23:14 by keys              #+#    #+#             */
/*   Updated: 2023/03/04 21:30:30 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qq_flag(bool *sq, bool *dq, char c)
{
	if (c == '\"')
	{
		if (!(*sq))
			*dq = !*dq;
	}
	else if (c == '\'')
	{
		if (!(*dq))
			*sq = !*sq;
	}
}

bool	quate_flag(char *prompt, size_t *len, bool *dq, bool *sq)
{
	if (prompt[*len] == '\"' || prompt[*len] == '\'')
	{
		qq_flag(sq, dq, prompt[*len]);
		*len += 1;
		return (true);
	}
	return (false);
}
