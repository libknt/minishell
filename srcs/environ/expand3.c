/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <marai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 00:36:02 by marai             #+#    #+#             */
/*   Updated: 2023/06/24 22:58:38 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s) && *s != '=')
			return (false);
		if (*s == '=')
			return (true);
		s++;
	}
	return (true);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"' || c == '`');
}

bool	is_heredoc_flag(char *word)
{
	if (ft_strncmp(word, "<<", 2) == 0)
		return (true);
	return (false);
}
