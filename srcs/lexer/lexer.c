/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 16:16:08 by keys              #+#    #+#             */
/*   Updated: 2023/02/10 16:33:28 by keys             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_metacharacter(char c)
{
	char	*is;

	is = strchr("|&;()<> \t", c);
	if (is == NULL)
		return (false);
	return (true);
}

t_token	*lexer(char *prompt)
{
	size_t	len;
	t_token *token;

	while(1)
	{
		while(is_blank(*prompt))
			prompt++;
		if(!*prompt)
			break;
		len = word(prompt);
		if(len == 0)
			break;
		else{
			// set
		}
	}

}
