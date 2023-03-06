/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_is.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keys <keys@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 21:12:35 by keys              #+#    #+#             */
/*   Updated: 2023/03/04 21:29:44 by keys             ###   ########.fr       */
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

size_t	is_ope(char *line)
{
	if (strncmp(line, "||", 2) == 0 || strncmp(line, "&&", 2) == 0 \
	|| strncmp(line, ";;", 2) == 0 || strncmp(line, "|&", 2) == 0)
		return (2);
	if (strncmp(line, "&", 1) == 0 || strncmp(line, ";", 1) == 0 \
	|| strncmp(line, "(", 1) == 0 || strncmp(line, ")", 1) == 0 \
	|| strncmp(line, "|", 1) == 0 || strncmp(line, "\n", 1) == 0)
		return (1);
	return (0);
}

size_t	is_redirect(char *line)
{
	if ((strncmp(line, "<<", 2) == 0) || (strncmp(line, ">>", 2) == 0))
		return (2);
	if ((strncmp(line, "<", 1) == 0) || (strncmp(line, ">", 1) == 0))
		return (1);
	return (0);
}

bool	is_ok(char *prompt, size_t len)
{
	if (is_blank(prompt[len]) || (prompt[len] == '\0') \
	|| is_ope(&prompt[len]) || (strncmp(&prompt[len], "<", 1) == 0) \
	|| (strncmp(&prompt[len], ">", 1) == 0))
		return (true);
	return (false);
}
